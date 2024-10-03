/*****************************************************************************
******************************************************************************
*
*               Real-Time main for use with Simulink Desktop Real-Time
*
*               Copyright 1994-2021 The MathWorks, Inc.
*
******************************************************************************
*****************************************************************************/


/*
*
* Defines used:
*      RT              - Required.
*      MODEL=modelname - Required.
*      NUMST=#         - Required. Number of sample times.
*      NCSTATES=#      - Required. Number of continuous states.
*      TID01EQ=1 or 0  - Optional. Only define to 1 if sample time task
*                        id's 0 and 1 have equal rates.
*/

#include <rtwtypes.h>
#include <rtmodel.h>
#include <rt_sim.h>
#include <rt_nonfinite.h>

#include <ext_svr.h>
#include <ext_share.h>
#include <ext_svr_transport.h>
#include <updown.h>

#include <rterror.h>
#include <sldrtdef.h>
#include <sldrtextmode.h>


#if TID01EQ == 1
#define FIRST_TID 1
#else
#define FIRST_TID 0
#endif

#ifndef RT
#error "must define RT"
#endif

#ifndef MODEL
#error "must define MODEL"
#endif

#ifndef NUMST
#error "must define number of sample times, NUMST"
#endif

#ifndef NCSTATES
#error "must define NCSTATES"
#endif

/* target connection support */
#ifdef TGTCONN
  EXTERN_C const char *TgtConnInit(int_T argc, char_T *argv[]);
  EXTERN_C void TgtConnTerm();
  EXTERN_C void TgtConnPreStep(int_T tid);
  EXTERN_C void TgtConnPostStep(int_T tid);
#else
  #define TgtConnInit(argc, argv) NULL /* do nothing */
  #define TgtConnTerm()                /* do nothing */
  #define TgtConnPreStep(tid)          /* do nothing */
  #define TgtConnPostStep(tid)         /* do nothing */
#endif


#define str(s)     #s
#define xstr(s)    str(s)
#define MODEL_NAME xstr(MODEL)

#define RUN_FOREVER -1.0

/* define RTMODEL type and structure name */
#define EXPAND_CONCAT(name1,name2) name1##name2
#define CONCAT(name1,name2)        EXPAND_CONCAT(name1, name2)
#define RTMODELTYPE                CONCAT(CONCAT(RT_MODEL_, MODEL),_T)


EXTERN_C RTMODELTYPE* MODEL(void);
static RTMODELTYPE* S;


EXTERN_C void MdlInitializeSizes(void);
EXTERN_C void MdlInitializeSampleTimes(void);
EXTERN_C void MdlStart(void);
EXTERN_C void MdlOutputs(int_T tid);
EXTERN_C void MdlUpdate(int_T tid);
EXTERN_C void MdlTerminate(void);

#if NCSTATES > 0
  EXTERN_C void rt_ODECreateIntegrationData(RTWSolverInfo *si);
  EXTERN_C void rt_ODEUpdateContinuousStates(RTWSolverInfo *si);

  #define rt_CreateIntegrationData(S)  rt_ODECreateIntegrationData(rtmGetRTWSolverInfo(S))
  #define rt_UpdateContinuousStates(S) rt_ODEUpdateContinuousStates(rtmGetRTWSolverInfo(S))
#else /* NCSTATES == 0 */
  #define rt_CreateIntegrationData(S)  rtsiSetSolverName(rtmGetRTWSolverInfo(S),"FixedStepDiscrete")
  #define rt_UpdateContinuousStates(S) /* Do Nothing */
#endif


/* flag to indicate an already stopped model */
static int_T modelStopped = 0;

extern size_t SB;   /* shared buffer structure - the first element is its size */
extern char uploadInfoArray[];   /* upload info array from updown.c */

EXTERN_C void SendShutdownPkt(void);

/* external mode compatibility variables */

volatile TargetSimStatus modelStatus = TARGET_STATUS_WAITING_TO_START;
volatile int_T startModel;



/*****************************************************************************
;*
;*		sim_initialize
;*		main simulation initialization
;*
;*		Input:	none
;*		Output:	error
;*
;****************************************************************************/

int sim_initialize(void)
{
const char* status;
int error;

/* create external mode data structures */
#ifdef EXT_MODE
  ExtParseArgsAndInitUD(0, NULL);
#endif /* EXT_MODE */
TgtConnInit(0, NULL);

/* initialize the model */
rt_InitInfAndNaN(sizeof(real_T));
S = MODEL();

MdlInitializeSizes();
MdlInitializeSampleTimes();

status = rt_SimInitTimingEngine(rtmGetNumSampleTimes(S),
                                rtmGetStepSize(S),
                                rtmGetSampleTimePtr(S),
                                rtmGetOffsetTimePtr(S),
                                rtmGetSampleHitPtr(S),
                                rtmGetSampleTimeTaskIDPtr(S),
                                rtmGetTStart(S),
                                &rtmGetSimTimeStep(S),
                                &rtmGetTimingData(S));

if (status != NULL)
  return(ERR_SIMNOTINIT);

rt_CreateIntegrationData(S);

#ifdef EXT_MODE
if (rt_ExtModeInit() != EXT_NO_ERROR)
  return(ERR_SIMNOTINIT);
#endif /* EXT_MODE */

modelStopped = 0;

// RTBIO_DriverIO(0, STREAMOUTPUT, IOWRITE, 1, NULL, (double *) "\x00", NULL);

return(ERR_OK);
}



/*****************************************************************************
;*
;*		DISABLE
;*		disable the model
;*
;*		Input:	none
;*		Output:	none
;*
;****************************************************************************/

RXCALL void Disable(void)
{
//  MdlTerminate();

  TgtConnTerm();
#ifdef EXT_MODE
  rt_ExtModeShutdown(rtmGetNumSampleTimes(S));
#endif // EXT_MODE

}


/*****************************************************************************
;*
;*              EXTMODEADDTIMEPOINT
;*              add one time point to external mode upload buffers
;*
;*              Input:  task id
;*                      is this a base rate or not
;*              Output: none
;*
;****************************************************************************/

static void ExtModeAddTimePoint(int_T tid, boolean_T baserate)
{
#ifdef EXT_MODE
  int j;

  for (j=0; j<NUM_UPINFOS; ++j)
  {
    if (baserate)
      UploadCheckTrigger(j, rtmGetNumSampleTimes(S));

#ifdef MULTITASKING
    /* for multitasking, sample hit is guaranteed */
    UploadBufAddTimePoint(tid, rtmGetTaskTime(S, tid), j);

#else  /* SINGLETASKING */
    /* for singletasking, upload only at sample hits */
    {
      int i;
      for (i=tid; i<NUMST; ++i)
        if (rtmIsSampleHit(S, i, 0))
          UploadBufAddTimePoint(i, rtmGetTaskTime(S, i), j);
    }
#endif  /* MULTITASKING or SINGLETASKING */

    /* check for end of the trigger */
    if (baserate)
      UploadCheckEndTrigger(j);
  }

#endif  /* EXT_MODE */
}


/*****************************************************************************
;*
;*		EXECUTE
;*		execute the model
;*
;*		Input:	tid = task id
;*		Output:	step size
;*
;****************************************************************************/

RXCALL double Execute(int tid)
{
  /* don't do anything if already stopped */
  if (modelStopped)
    return(ERR_OK);

  if (rtmGetT(S)==0)
  {
    /* initialize timing */
    sldrt_initialize_timing();
  }

  /* the first two TIDs are served by one timer if equal */
  if (tid>0)
    tid += FIRST_TID;

  /*********************************/
  /* process multitasking subrates */
  /*********************************/

#ifdef MULTITASKING
  /* TID!=0 : multitasking subrate */
  if (tid != 0)
  {
    TgtConnPreStep(tid); /* Target connectivity Pre-MdlOutputs */
    MdlOutputs(tid);
    TgtConnPostStep(tid); /* Target connectivity Post-MdlOutputs */
    ExtModeAddTimePoint(tid, FALSE);  /* add the time point to upload buffer */
    MdlUpdate(tid);
    rt_SimUpdateDiscreteTaskTime(rtmGetTPtr(S), rtmGetTimingData(S), tid);
    return(rtmGetSampleTime(S, tid));
  }
#endif /* MULTITASKING */



  /*******************************************************/
  /* stop the execution if requested or time has elapsed */
  /*******************************************************/

  if (rtmGetStopRequested(S) || (rtmGetT(S) > rtmGetTFinal(S) && rtmGetTFinal(S) != RUN_FOREVER ) )
  {
    /* stop all tasks */
    modelStopped = 1;

    /* add the last time point to upload buffer */
    TgtConnPreStep(0); /* Target connectivity Pre-MdlOutputs */
//    MdlOutputs(0);
    TgtConnPostStep(0); /* Target connectivity Post-MdlOutputs */
//    ExtModeAddTimePoint(0, TRUE);

#ifdef EXT_MODE
    {
      /* terminate external mode */
      int j;

      for (j=0; j<NUM_UPINFOS; ++j)
        UploadPrepareForFinalFlush(j);
      SendShutdownPkt();
    }
#endif /* EXT_MODE */

    /* terminate simulation */
    MdlTerminate();
    return(rtmGetSampleTime(S, FIRST_TID));
  }


  /**************************/
  /* multitasking base rate */
  /**************************/

#ifdef MULTITASKING
   /* update discrete events */
  {
    real_T tnext = rt_SimUpdateDiscreteEvents(rtmGetNumSampleTimes(S),
                                              rtmGetTimingData(S),
                                              rtmGetSampleHitPtr(S),
                                              rtmGetPerTaskSampleHitsPtr(S));
    rtsiSetSolverStopTime(rtmGetRTWSolverInfo(S),tnext);
  }

  TgtConnPreStep(FIRST_TID); /* Target connectivity Pre-MdlOutputs */
  MdlOutputs(FIRST_TID);
  TgtConnPostStep(FIRST_TID); /* Target connectivity Post-MdlOutputs */
  ExtModeAddTimePoint(FIRST_TID, TRUE);     /* add the time point to upload buffer */
  MdlUpdate(FIRST_TID);
  if (rtmGetSampleTime(S, 0) == CONTINUOUS_SAMPLE_TIME)
    rt_UpdateContinuousStates(S);
  else
    rt_SimUpdateDiscreteTaskTime(rtmGetTPtr(S), rtmGetTimingData(S), 0);

#if FIRST_TID == 1
  rt_SimUpdateDiscreteTaskTime(rtmGetTPtr(S), rtmGetTimingData(S),1);
#endif


  /*****************/
  /* singletasking */
  /*****************/

#else /* SINGLETASKING */
  rtsiSetSolverStopTime(rtmGetRTWSolverInfo(S), rt_SimGetNextSampleHit());
  TgtConnPreStep(0); /* Target connectivity Pre-MdlOutputs */
  MdlOutputs(0);
  TgtConnPostStep(0); /* Target connectivity Post-MdlOutputs */
  ExtModeAddTimePoint(0, TRUE);     /* add the time point to upload buffer */
  MdlUpdate(0);
  rt_SimUpdateDiscreteTaskSampleHits(rtmGetNumSampleTimes(S),
                                     rtmGetTimingData(S),
                                     rtmGetSampleHitPtr(S),
                                     rtmGetTPtr(S));
  if (rtmGetSampleTime(S, 0) == CONTINUOUS_SAMPLE_TIME)
    rt_UpdateContinuousStates(S);

#endif /* MULTITASKING or SINGLETASKING */

  return(rtmGetSampleTime(S, tid));
}



/*****************************************************************************
;*
;*              COMM
;*              communicate with the compiled model
;*
;*              Input:  action code
;*                      action parameters
;*              Output: 0 if success, error code otherwise
;*
;****************************************************************************/

RXCALL int Comm(int action, void* param)
{
#ifdef EXT_MODE
switch (action)
{
  case EXT_INITIALIZE :
  {
    MdlStart();
  }
  break;

  case EXT_PROCESS_PKT :
  {
    boolean_T stopReq = 0;
    rt_PktServerWork(rtmGetRTWExtModeInfo(S),
                     rtmGetNumSampleTimes(S),
                     &stopReq);
    rtmSetStopRequested(S, stopReq);
  }
  break;

  case EXT_ENDLOGGINGSESSION :
  {
    int upInfoIdx = *((int *) param);
    UploadEndLoggingSession(upInfoIdx, rtmGetNumSampleTimes(S));
  }
  break;
}
#endif /* EXT_MODE */

  return(0);
}


/*****************************************************************************
;*
;*              ENABLE
;*              initialize compiled model
;*
;*              Input:  none
;*              Output: 0 if success, error code otherwise
;*
;****************************************************************************/

#ifdef EXT_MODE
RawExtInfo ExtInfo;
#endif /* EXT_MODE */

RXCALL int Enable()
{
  int error;

  error=sim_initialize();
  if (error!=ERR_OK)
    return(error);

#ifdef EXT_MODE
  ExtInfo.NumSampleTimes = rtmGetNumSampleTimes(S);
  ExtInfo.ExtInfo = (size_t) rtmGetRTWExtModeInfo(S);
  ExtInfo.UploadInfo = (size_t) uploadInfoArray;
#endif /* EXT_MODE */

  return(ERR_OK);
}
