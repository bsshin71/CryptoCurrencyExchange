/***********************************************
 * This code is inserted automatically by gpec
 ***********************************************/
#include <goldilocksesql.h>
typedef struct {
  int mCharMap;
} zlpOption;
static zlpOption gZlpOption = {1};
/***********************************************
 * End of gpec automatic inclusion
 ***********************************************/


#line __LINE__ "Goldilocks.cc"

#include <Goldilocks.hpp> 
#include <cstring>
#include <limits.h>
#include <BCMath.hpp>



/* EXEC SQL INCLUDE SQLCA; */
#include "sqlca.h"
#line 9 "Goldilocks.gc"

/* EXEC SQL INCLUDE ./GoldilocksStruct.hpp; */

/* EXEC SQL BEGIN DECLARE SECTION ; */
#line 2 "./GoldilocksStruct.hpp"
 

typedef unsigned int uint64 ;


const int MAX_FLOATING_LENGTH = 31;
const int MAX_COIN_NAME_LENGTH = 50; 

typedef struct { 
  char     mCoin[MAX_COIN_NAME_LENGTH];
  uint64   mTicketNo;  // Request No 
  int      mPosition;   // Position   : filled by caller 
  uint64   mPrice;      // Price      : filled by caller 
  char     mQty[MAX_FLOATING_LENGTH]; // Quantity   : filled by caller 
  char     mAvailQty[MAX_FLOATING_LENGTH];   // Available Quantity 
  int      mProcess;    // Process    
  int      mOrderType;  // Order Type : filled by caller 
  uint64   mOrderNo ;   // Order No   : filled by caller. must be unique.
} DBRequest; 

typedef struct { 
  uint64  mPrice ; 
  char    mQty[MAX_FLOATING_LENGTH];  
  uint64  mAskNo ; 
  uint64  mBidNo ; 
} DBFill ; 


typedef struct 
{
  int     mBidQueue ; 
  char    mBidQty[MAX_FLOATING_LENGTH];
  uint64  mPrice    ; 
  char    mAskQty[MAX_FLOATING_LENGTH]; 
  int     mAskQueue ; 
} Offer;



/* EXEC SQL END DECLARE SECTION ; */
#line 41 "./GoldilocksStruct.hpp"
 


#line 10 "Goldilocks.gc"


#define CHECK_ERROR  checkSQLError ( ) 
namespace exchange {



static int checkSQLError ( ) 
{

  if ( sqlca.sqlcode != SQL_SUCCESS ) 
  {
    throw ExchangeDBException (sqlca.sqlerrm.sqlerrmc );
  } 
  return 0;
}


Goldilocks::Goldilocks (const std::string& aUser, 
                        const std::string& aPassword, 
                        const std::string& aDSN, 
                        const int aLogOption, 
                        const int aScale 
                        ) : 
     
    mUser (aUser), mPassword (aPassword), 
    mDSN(aDSN), mLogOption (aLogOption), 
    mScale(aScale), mIsOpened ( 0 ) 
  {} 

Goldilocks::~Goldilocks () 
{
  for ( auto it = mQueryMap.begin () ; 
       it != mQueryMap.end() ; ++it ) 
  {
    free( it->second ) ;
  }
}

int Goldilocks :: OpenDatabase ()  
{
  const int MAX_STRING_LEN = 1024;
  /* EXEC SQL BEGIN DECLARE SECTION ; */
#line 52 "Goldilocks.gc"

  char sUserName [MAX_STRING_LEN];
  char sPassword [MAX_STRING_LEN];
  char sDSN [MAX_STRING_LEN] ;
  /* EXEC SQL END   DECLARE SECTION ; */
#line 56 "Goldilocks.gc"


  // Copy argument to host variables 
  std::strncpy ( sUserName, mUser.c_str (), MAX_STRING_LEN) ;
  std::strncpy ( sPassword, mPassword.c_str(), MAX_STRING_LEN);
  std::strncpy ( sDSN, mDSN.c_str(), MAX_STRING_LEN);

  /* EXEC SQL CONNECT :sUserName IDENTIFIED BY :sPassword USING :sDSN  */
{
    sqlargs_t sqlargs;
#line 137 "Goldilocks.cc"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 35;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.iters = 0;
    DBESQL_Connect(NULL, &sqlargs, sDSN, sUserName, sPassword);
}
#line 63 "Goldilocks.gc"
 
  CHECK_ERROR;

  mIsOpened = 1; 
  /* EXEC SQL AUTOCOMMIT OFF ; */
{
    sqlargs_t sqlargs;
#line 171 "Goldilocks.cc"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 23;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.iters = 0;
    DBESQL_SetAutoCommit(NULL, &sqlargs, 0);
}
#line 67 "Goldilocks.gc"
 
  CHECK_ERROR;
  

  return 0;
} 


int Goldilocks :: buildQueryMap() 
{
  return 0;

}


int Goldilocks :: BeginTransaction ()  
{
  return SUCCESS ;
}


int Goldilocks :: Commit ()  
{
  /* EXEC SQL COMMIT  */
{
    sqlargs_t sqlargs;
#line 224 "Goldilocks.cc"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 18;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.iters = 0;
    DBESQL_EndTran(NULL, &sqlargs, 1, 0);
}
#line 90 "Goldilocks.gc"
 
  CHECK_ERROR;

  
  return SUCCESS ;
}


int Goldilocks :: Rollback ()  
{
  /* EXEC SQL ROLLBACK */
{
    sqlargs_t sqlargs;
#line 264 "Goldilocks.cc"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 19;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.iters = 0;
    DBESQL_EndTran(NULL, &sqlargs, 0, 0);
}
#line 100 "Goldilocks.gc"

  CHECK_ERROR;

  
  return SUCCESS ;
}

int Goldilocks :: CloseDatabase ()  
{

  if ( mIsOpened ) 
  {
    /* EXEC SQL ROLLBACK  */
{
    sqlargs_t sqlargs;
#line 306 "Goldilocks.cc"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 19;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.iters = 0;
    DBESQL_EndTran(NULL, &sqlargs, 0, 0);
}
#line 112 "Goldilocks.gc"
 
    CHECK_ERROR;
    /* EXEC SQL DISCONNECT  */
{
    sqlargs_t sqlargs;
#line 338 "Goldilocks.cc"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 35;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.iters = 0;
    DBESQL_Disconnect(NULL, &sqlargs, NULL, 0);
}
#line 114 "Goldilocks.gc"

    CHECK_ERROR;
  }
  return SUCCESS ;
}


int Goldilocks :: InsertNewRequest ( DBRequest* aRequest ) 
{
  /* EXEC SQL BEGIN DECLARE SECTION ; */
#line 123 "Goldilocks.gc"

  DBRequest *sInRecord;
  /* EXEC SQL END   DECLARE SECTION ; */
#line 125 "Goldilocks.gc"


  sInRecord = aRequest;

  /* EXEC SQL SELECT TICKET_SEQ.NEXTVAL INTO :sInRecord__mTicketNo FROM DUAL  */
{
    sqlargs_t sqlargs;
#line 387 "Goldilocks.cc"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 2;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = (char *)"SELECT TICKET_SEQ.NEXTVAL INTO :sInRecord__mTicketNo FROM DUAL \n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.iters = 0;
    sqlhv_t sqlhv[1];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 1;
    sqlhv[0].io_type = 1;
    sqlhv[0].data_type = 6;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = sizeof(sInRecord->mTicketNo);
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(sInRecord->mTicketNo);
    sqlhv[0].value = (void *)&sInRecord->mTicketNo;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].ptr_size = -1;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 129 "Goldilocks.gc"

  CHECK_ERROR;

  /* EXEC SQL INSERT INTO FILL_REQUEST (COIN, TICKET_NO, REQ_TIME, POSITION,
                                     PRICE, REQ_QTY, AVAIL_QTY, PROCESS,
                                     ORDER_TYPE, ORDER_NO ) 
      VALUES ( :sInRecord__mCoin, :sInRecord__mTicketNo, SYSTIMESTAMP,
               :sInRecord__mPosition, :sInRecord__mPrice, :sInRecord__mQty,
               :sInRecord__mQty, :sInRecord__mProcess, :sInRecord__mOrderType, 
               :sInRecord__mOrderNo )  */
{
    sqlargs_t sqlargs;
#line 442 "Goldilocks.cc"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 6;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = (char *)"INSERT INTO FILL_REQUEST (COIN, TICKET_NO, REQ_TIME, POSITION,\n"
"                                     PRICE, REQ_QTY, AVAIL_QTY, PROCESS,\n"
"                                     ORDER_TYPE, ORDER_NO ) \n"
"      VALUES ( :sInRecord__mCoin, :sInRecord__mTicketNo, SYSTIMESTAMP,\n"
"               :sInRecord__mPosition, :sInRecord__mPrice, :sInRecord__mQty,\n"
"               :sInRecord__mQty, :sInRecord__mProcess, :sInRecord__mOrderType, \n"
"               :sInRecord__mOrderNo ) \n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.iters = 0;
    sqlhv_t sqlhv[9];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 9;
    sqlhv[0].io_type = 0;
    sqlhv[0].data_type = 13;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = MAX_COIN_NAME_LENGTH;
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(sInRecord->mCoin);
    sqlhv[0].value = (void *)sInRecord->mCoin;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].ptr_size = -1;
    sqlhv[1].io_type = 0;
    sqlhv[1].data_type = 6;
    sqlhv[1].arr_size = 0;
    sqlhv[1].buflen = sizeof(sInRecord->mTicketNo);
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(sInRecord->mTicketNo);
    sqlhv[1].value = (void *)&sInRecord->mTicketNo;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].ptr_size = -1;
    sqlhv[2].io_type = 0;
    sqlhv[2].data_type = 5;
    sqlhv[2].arr_size = 0;
    sqlhv[2].buflen = sizeof(sInRecord->mPosition);
    sqlhv[2].precision = 0;
    sqlhv[2].scale = 0;
    sqlhv[2].el_size = sizeof(sInRecord->mPosition);
    sqlhv[2].value = (void *)&sInRecord->mPosition;
    sqlhv[2].ind_type = -1;
    sqlhv[2].ind_el_size = 0;
    sqlhv[2].indicator = NULL;
    sqlhv[2].ptr_size = -1;
    sqlhv[3].io_type = 0;
    sqlhv[3].data_type = 6;
    sqlhv[3].arr_size = 0;
    sqlhv[3].buflen = sizeof(sInRecord->mPrice);
    sqlhv[3].precision = 0;
    sqlhv[3].scale = 0;
    sqlhv[3].el_size = sizeof(sInRecord->mPrice);
    sqlhv[3].value = (void *)&sInRecord->mPrice;
    sqlhv[3].ind_type = -1;
    sqlhv[3].ind_el_size = 0;
    sqlhv[3].indicator = NULL;
    sqlhv[3].ptr_size = -1;
    sqlhv[4].io_type = 0;
    sqlhv[4].data_type = 13;
    sqlhv[4].arr_size = 0;
    sqlhv[4].buflen = MAX_FLOATING_LENGTH;
    sqlhv[4].precision = 0;
    sqlhv[4].scale = 0;
    sqlhv[4].el_size = sizeof(sInRecord->mQty);
    sqlhv[4].value = (void *)sInRecord->mQty;
    sqlhv[4].ind_type = -1;
    sqlhv[4].ind_el_size = 0;
    sqlhv[4].indicator = NULL;
    sqlhv[4].ptr_size = -1;
    sqlhv[5].io_type = 0;
    sqlhv[5].data_type = 13;
    sqlhv[5].arr_size = 0;
    sqlhv[5].buflen = MAX_FLOATING_LENGTH;
    sqlhv[5].precision = 0;
    sqlhv[5].scale = 0;
    sqlhv[5].el_size = sizeof(sInRecord->mQty);
    sqlhv[5].value = (void *)sInRecord->mQty;
    sqlhv[5].ind_type = -1;
    sqlhv[5].ind_el_size = 0;
    sqlhv[5].indicator = NULL;
    sqlhv[5].ptr_size = -1;
    sqlhv[6].io_type = 0;
    sqlhv[6].data_type = 5;
    sqlhv[6].arr_size = 0;
    sqlhv[6].buflen = sizeof(sInRecord->mProcess);
    sqlhv[6].precision = 0;
    sqlhv[6].scale = 0;
    sqlhv[6].el_size = sizeof(sInRecord->mProcess);
    sqlhv[6].value = (void *)&sInRecord->mProcess;
    sqlhv[6].ind_type = -1;
    sqlhv[6].ind_el_size = 0;
    sqlhv[6].indicator = NULL;
    sqlhv[6].ptr_size = -1;
    sqlhv[7].io_type = 0;
    sqlhv[7].data_type = 5;
    sqlhv[7].arr_size = 0;
    sqlhv[7].buflen = sizeof(sInRecord->mOrderType);
    sqlhv[7].precision = 0;
    sqlhv[7].scale = 0;
    sqlhv[7].el_size = sizeof(sInRecord->mOrderType);
    sqlhv[7].value = (void *)&sInRecord->mOrderType;
    sqlhv[7].ind_type = -1;
    sqlhv[7].ind_el_size = 0;
    sqlhv[7].indicator = NULL;
    sqlhv[7].ptr_size = -1;
    sqlhv[8].io_type = 0;
    sqlhv[8].data_type = 6;
    sqlhv[8].arr_size = 0;
    sqlhv[8].buflen = sizeof(sInRecord->mOrderNo);
    sqlhv[8].precision = 0;
    sqlhv[8].scale = 0;
    sqlhv[8].el_size = sizeof(sInRecord->mOrderNo);
    sqlhv[8].value = (void *)&sInRecord->mOrderNo;
    sqlhv[8].ind_type = -1;
    sqlhv[8].ind_el_size = 0;
    sqlhv[8].indicator = NULL;
    sqlhv[8].ptr_size = -1;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 138 "Goldilocks.gc"

  CHECK_ERROR;
  
  

  return 0; 
}

int Goldilocks :: FindMatchRecords (DBRequest* aRequest, 
                                    ResultVector& aVector ) 
{
  /* EXEC SQL BEGIN DECLARE SECTION ; */
#line 149 "Goldilocks.gc"

  DBRequest *sInRecord; 
  DBRequest sOutRecord; 
  /* EXEC SQL END   DECLARE SECTION ; */
#line 152 "Goldilocks.gc"


  sInRecord = aRequest;

  BCMath sTotal ( 0 ) ; 
  BCMath sRequestQty ( std::string( sInRecord->mQty ) ) ;

  if ( sInRecord->mOrderType == MARKET_ORDER ) 
  {

    switch ( sInRecord->mPosition ) 
    {
      case ASK : 
        sInRecord->mPrice = 0 ;  
        break; 
      case BID : 
        sInRecord->mPrice = 10000000000 ; 
        break; 
    } 
  }
  

  /* EXEC SQL 
      DECLARE SELECT_CURSOR CURSOR FOR 
       SELECT  /g+ INDEX (X, IDX_FILL_REQUEST_ASK) g/
              COIN, 
              TICKET_NO, 
              POSITION, 
              PRICE, 
              REQ_QTY, 
              AVAIL_QTY, 
              PROCESS, 
              ORDER_TYPE, 
              ORDER_NO
       FROM   FILL_REQUEST X
       WHERE  X.POSITION = 0
        AND   X.COIN = :sInRecord__mCoin
        AND   X.PROCESS = 1 
        AND   X.AVAIL_QTY > 0 
        AND   X.PRICE <= :sInRecord__mPrice 
        AND   1 = :sInRecord__mPosition 
       UNION ALL 
       SELECT /g+ INDEX (X, IDX_FILL_REQUEST_BID) g/
              COIN, 
              TICKET_NO, 
              POSITION, 
              PRICE, 
              REQ_QTY, 
              AVAIL_QTY, 
              PROCESS, 
              ORDER_TYPE, 
              ORDER_NO
       FROM   FILL_REQUEST X
       WHERE  X.POSITION = 1
        AND   X.COIN = :sInRecord__mCoin
        AND   X.PROCESS = 1 
        AND   X.AVAIL_QTY > 0 
        AND   X.PRICE >= :sInRecord__mPrice
        AND   0 = :sInRecord__mPosition
         */
{
    sqlargs_t sqlargs;
#line 667 "Goldilocks.cc"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 25;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.iters = 0;
    DBESQL_DeclareCursor(NULL, &sqlargs);
}
#line 211 "Goldilocks.gc"
 



  CHECK_ERROR;
  /* EXEC SQL OPEN SELECT_CURSOR  */
{
    sqlargs_t sqlargs;
#line 702 "Goldilocks.cc"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 26;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = (char *)"SELECT  /*+ INDEX (X, IDX_FILL_REQUEST_ASK) */\n"
"              COIN, \n"
"              TICKET_NO, \n"
"              POSITION, \n"
"              PRICE, \n"
"              REQ_QTY, \n"
"              AVAIL_QTY, \n"
"              PROCESS, \n"
"              ORDER_TYPE, \n"
"              ORDER_NO\n"
"       FROM   FILL_REQUEST X\n"
"       WHERE  X.POSITION = 0\n"
"        AND   X.COIN = :sInRecord__mCoin\n"
"        AND   X.PROCESS = 1 \n"
"        AND   X.AVAIL_QTY > 0 \n"
"        AND   X.PRICE <= :sInRecord__mPrice \n"
"        AND   1 = :sInRecord__mPosition \n"
"       UNION ALL \n"
"       SELECT /*+ INDEX (X, IDX_FILL_REQUEST_BID) */\n"
"              COIN, \n"
"              TICKET_NO, \n"
"              POSITION, \n"
"              PRICE, \n"
"              REQ_QTY, \n"
"              AVAIL_QTY, \n"
"              PROCESS, \n"
"              ORDER_TYPE, \n"
"              ORDER_NO\n"
"       FROM   FILL_REQUEST X\n"
"       WHERE  X.POSITION = 1\n"
"        AND   X.COIN = :sInRecord__mCoin\n"
"        AND   X.PROCESS = 1 \n"
"        AND   X.AVAIL_QTY > 0 \n"
"        AND   X.PRICE >= :sInRecord__mPrice\n"
"        AND   0 = :sInRecord__mPosition\n"
"        \n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.iters = 0;
    sqlcurprops_t sqlcurprops;
    sqlcursor_t   sqlcursor;
#line 764 "Goldilocks.cc"
    sqlcursor.sqlcurprops = &sqlcurprops;
    sqlargs.sqlcursor = &sqlcursor;
    sqlcursor.sqlcname = (char *)"SELECT_CURSOR";
    sqlcursor.sqldynstmt = NULL;
    sqlcurprops.org_type = 1;
    sqlcurprops.cur_type = 1;
    sqlcurprops.sensitivity = 0;
    sqlcurprops.scrollability = 0;
    sqlcurprops.holdability = 0;
    sqlcurprops.updatability = 0;
    sqlcurprops.returnability = 0;
    sqlhv_t sqlhv[6];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 6;
    sqlhv[0].io_type = 0;
    sqlhv[0].data_type = 13;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = MAX_COIN_NAME_LENGTH;
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(sInRecord->mCoin);
    sqlhv[0].value = (void *)sInRecord->mCoin;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].ptr_size = -1;
    sqlhv[1].io_type = 0;
    sqlhv[1].data_type = 6;
    sqlhv[1].arr_size = 0;
    sqlhv[1].buflen = sizeof(sInRecord->mPrice);
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(sInRecord->mPrice);
    sqlhv[1].value = (void *)&sInRecord->mPrice;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].ptr_size = -1;
    sqlhv[2].io_type = 0;
    sqlhv[2].data_type = 5;
    sqlhv[2].arr_size = 0;
    sqlhv[2].buflen = sizeof(sInRecord->mPosition);
    sqlhv[2].precision = 0;
    sqlhv[2].scale = 0;
    sqlhv[2].el_size = sizeof(sInRecord->mPosition);
    sqlhv[2].value = (void *)&sInRecord->mPosition;
    sqlhv[2].ind_type = -1;
    sqlhv[2].ind_el_size = 0;
    sqlhv[2].indicator = NULL;
    sqlhv[2].ptr_size = -1;
    sqlhv[3].io_type = 0;
    sqlhv[3].data_type = 13;
    sqlhv[3].arr_size = 0;
    sqlhv[3].buflen = MAX_COIN_NAME_LENGTH;
    sqlhv[3].precision = 0;
    sqlhv[3].scale = 0;
    sqlhv[3].el_size = sizeof(sInRecord->mCoin);
    sqlhv[3].value = (void *)sInRecord->mCoin;
    sqlhv[3].ind_type = -1;
    sqlhv[3].ind_el_size = 0;
    sqlhv[3].indicator = NULL;
    sqlhv[3].ptr_size = -1;
    sqlhv[4].io_type = 0;
    sqlhv[4].data_type = 6;
    sqlhv[4].arr_size = 0;
    sqlhv[4].buflen = sizeof(sInRecord->mPrice);
    sqlhv[4].precision = 0;
    sqlhv[4].scale = 0;
    sqlhv[4].el_size = sizeof(sInRecord->mPrice);
    sqlhv[4].value = (void *)&sInRecord->mPrice;
    sqlhv[4].ind_type = -1;
    sqlhv[4].ind_el_size = 0;
    sqlhv[4].indicator = NULL;
    sqlhv[4].ptr_size = -1;
    sqlhv[5].io_type = 0;
    sqlhv[5].data_type = 5;
    sqlhv[5].arr_size = 0;
    sqlhv[5].buflen = sizeof(sInRecord->mPosition);
    sqlhv[5].precision = 0;
    sqlhv[5].scale = 0;
    sqlhv[5].el_size = sizeof(sInRecord->mPosition);
    sqlhv[5].value = (void *)&sInRecord->mPosition;
    sqlhv[5].ind_type = -1;
    sqlhv[5].ind_el_size = 0;
    sqlhv[5].indicator = NULL;
    sqlhv[5].ptr_size = -1;
    DBESQL_OpenCursor(NULL, &sqlargs);
}
#line 216 "Goldilocks.gc"
 

  

  while ( true ) 
  {
    /* EXEC SQL FETCH NEXT SELECT_CURSOR INTO :sOutRecord */
{
    sqlargs_t sqlargs;
#line 863 "Goldilocks.cc"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 28;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.iters = 0;
    sqlfetch_t   sqlfetch;
    sqlfetch.sqlfph = 0;
    sqlfetch.sqlfpl = 0;
    sqlfetch.offsethv = NULL;
    sqlargs.sqlfetch = &sqlfetch;
    sqlfetch.sqlcname = (char *)"SELECT_CURSOR";
    sqlfetch.sqlfo = 1;
    sqlfetch.sqlfph = (0L >> 32) & 0xFFFFFFFF;
    sqlfetch.sqlfpl = 0L & 0xFFFFFFFF;
    sqlfetch.offsethv = NULL;
    sqlhv_t sqlhv[9];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 9;
    sqlhv[0].io_type = 1;
    sqlhv[0].data_type = 13;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = MAX_COIN_NAME_LENGTH;
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(sOutRecord.mCoin);
    sqlhv[0].value = (void *)sOutRecord.mCoin;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].ptr_size = -1;
    sqlhv[1].io_type = 1;
    sqlhv[1].data_type = 6;
    sqlhv[1].arr_size = 0;
    sqlhv[1].buflen = sizeof(sOutRecord.mTicketNo);
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(sOutRecord.mTicketNo);
    sqlhv[1].value = (void *)&sOutRecord.mTicketNo;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].ptr_size = -1;
    sqlhv[2].io_type = 1;
    sqlhv[2].data_type = 5;
    sqlhv[2].arr_size = 0;
    sqlhv[2].buflen = sizeof(sOutRecord.mPosition);
    sqlhv[2].precision = 0;
    sqlhv[2].scale = 0;
    sqlhv[2].el_size = sizeof(sOutRecord.mPosition);
    sqlhv[2].value = (void *)&sOutRecord.mPosition;
    sqlhv[2].ind_type = -1;
    sqlhv[2].ind_el_size = 0;
    sqlhv[2].indicator = NULL;
    sqlhv[2].ptr_size = -1;
    sqlhv[3].io_type = 1;
    sqlhv[3].data_type = 6;
    sqlhv[3].arr_size = 0;
    sqlhv[3].buflen = sizeof(sOutRecord.mPrice);
    sqlhv[3].precision = 0;
    sqlhv[3].scale = 0;
    sqlhv[3].el_size = sizeof(sOutRecord.mPrice);
    sqlhv[3].value = (void *)&sOutRecord.mPrice;
    sqlhv[3].ind_type = -1;
    sqlhv[3].ind_el_size = 0;
    sqlhv[3].indicator = NULL;
    sqlhv[3].ptr_size = -1;
    sqlhv[4].io_type = 1;
    sqlhv[4].data_type = 13;
    sqlhv[4].arr_size = 0;
    sqlhv[4].buflen = MAX_FLOATING_LENGTH;
    sqlhv[4].precision = 0;
    sqlhv[4].scale = 0;
    sqlhv[4].el_size = sizeof(sOutRecord.mQty);
    sqlhv[4].value = (void *)sOutRecord.mQty;
    sqlhv[4].ind_type = -1;
    sqlhv[4].ind_el_size = 0;
    sqlhv[4].indicator = NULL;
    sqlhv[4].ptr_size = -1;
    sqlhv[5].io_type = 1;
    sqlhv[5].data_type = 13;
    sqlhv[5].arr_size = 0;
    sqlhv[5].buflen = MAX_FLOATING_LENGTH;
    sqlhv[5].precision = 0;
    sqlhv[5].scale = 0;
    sqlhv[5].el_size = sizeof(sOutRecord.mAvailQty);
    sqlhv[5].value = (void *)sOutRecord.mAvailQty;
    sqlhv[5].ind_type = -1;
    sqlhv[5].ind_el_size = 0;
    sqlhv[5].indicator = NULL;
    sqlhv[5].ptr_size = -1;
    sqlhv[6].io_type = 1;
    sqlhv[6].data_type = 5;
    sqlhv[6].arr_size = 0;
    sqlhv[6].buflen = sizeof(sOutRecord.mProcess);
    sqlhv[6].precision = 0;
    sqlhv[6].scale = 0;
    sqlhv[6].el_size = sizeof(sOutRecord.mProcess);
    sqlhv[6].value = (void *)&sOutRecord.mProcess;
    sqlhv[6].ind_type = -1;
    sqlhv[6].ind_el_size = 0;
    sqlhv[6].indicator = NULL;
    sqlhv[6].ptr_size = -1;
    sqlhv[7].io_type = 1;
    sqlhv[7].data_type = 5;
    sqlhv[7].arr_size = 0;
    sqlhv[7].buflen = sizeof(sOutRecord.mOrderType);
    sqlhv[7].precision = 0;
    sqlhv[7].scale = 0;
    sqlhv[7].el_size = sizeof(sOutRecord.mOrderType);
    sqlhv[7].value = (void *)&sOutRecord.mOrderType;
    sqlhv[7].ind_type = -1;
    sqlhv[7].ind_el_size = 0;
    sqlhv[7].indicator = NULL;
    sqlhv[7].ptr_size = -1;
    sqlhv[8].io_type = 1;
    sqlhv[8].data_type = 6;
    sqlhv[8].arr_size = 0;
    sqlhv[8].buflen = sizeof(sOutRecord.mOrderNo);
    sqlhv[8].precision = 0;
    sqlhv[8].scale = 0;
    sqlhv[8].el_size = sizeof(sOutRecord.mOrderNo);
    sqlhv[8].value = (void *)&sOutRecord.mOrderNo;
    sqlhv[8].ind_type = -1;
    sqlhv[8].ind_el_size = 0;
    sqlhv[8].indicator = NULL;
    sqlhv[8].ptr_size = -1;
    DBESQL_FetchCursor(NULL, &sqlargs);
}
#line 222 "Goldilocks.gc"
 
    if ( sqlca.sqlcode == SQL_NO_DATA ) 
    {
      break; 
    } 
    
    BCMath sToSum ( std::string ( sOutRecord.mAvailQty ) ) ;
    sTotal = sTotal + sToSum ;
    aVector.push_back ( sOutRecord ) ;
    if ( sRequestQty > sTotal ) 
    {
      continue; 
    }     
    break; 
  }

  /* EXEC SQL CLOSE SELECT_CURSOR  */
{
    sqlargs_t sqlargs;
#line 1030 "Goldilocks.cc"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 27;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = NULL;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.iters = 0;
    sqlcursor_t   sqlcursor;
    sqlargs.sqlcursor = &sqlcursor;
    sqlcursor.sqlcname = (char *)"SELECT_CURSOR";
    sqlcursor.sqlcurprops = NULL;
    DBESQL_CloseCursor(NULL, &sqlargs);
}
#line 238 "Goldilocks.gc"
 
  CHECK_ERROR;


  
  return 0; 
}

int Goldilocks :: AjustAvailQty (uint64 aNo, 
                                 char*  aCoin, 
                                 char*  aQty, 
                                 int aProcess ) 
{
  /* EXEC SQL BEGIN DECLARE SECTION ; */
#line 251 "Goldilocks.gc"

  uint64 sNo;
  char*   sQty; 
  char*   sCoin;
  int    sProcess ;
  /* EXEC SQL END   DECLARE SECTION ; */
#line 256 "Goldilocks.gc"


  sNo = aNo ;
  sProcess = aProcess;
  sQty = aQty; 
  sCoin = aCoin;



  /* EXEC SQL UPDATE FILL_REQUEST  
           SET AVAIL_QTY = :sQty, PROCESS= :sProcess 
           WHERE  COIN = :sCoin AND TICKET_NO = :sNo */
{
    sqlargs_t sqlargs;
#line 1097 "Goldilocks.cc"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 7;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = (char *)"UPDATE FILL_REQUEST  \n"
"           SET AVAIL_QTY = :sQty, PROCESS= :sProcess \n"
"           WHERE  COIN = :sCoin AND TICKET_NO = :sNo\n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.iters = 0;
    sqlhv_t sqlhv[4];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 4;
    sqlhv[0].io_type = 0;
    sqlhv[0].data_type = 13;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = 0;
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(sQty);
    sqlhv[0].value = (void *)sQty;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].ptr_size = -1;
    sqlhv[1].io_type = 0;
    sqlhv[1].data_type = 5;
    sqlhv[1].arr_size = 0;
    sqlhv[1].buflen = sizeof(sProcess);
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(sProcess);
    sqlhv[1].value = (void *)&sProcess;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].ptr_size = -1;
    sqlhv[2].io_type = 0;
    sqlhv[2].data_type = 13;
    sqlhv[2].arr_size = 0;
    sqlhv[2].buflen = 0;
    sqlhv[2].precision = 0;
    sqlhv[2].scale = 0;
    sqlhv[2].el_size = sizeof(sCoin);
    sqlhv[2].value = (void *)sCoin;
    sqlhv[2].ind_type = -1;
    sqlhv[2].ind_el_size = 0;
    sqlhv[2].indicator = NULL;
    sqlhv[2].ptr_size = -1;
    sqlhv[3].io_type = 0;
    sqlhv[3].data_type = 6;
    sqlhv[3].arr_size = 0;
    sqlhv[3].buflen = sizeof(sNo);
    sqlhv[3].precision = 0;
    sqlhv[3].scale = 0;
    sqlhv[3].el_size = sizeof(sNo);
    sqlhv[3].value = (void *)&sNo;
    sqlhv[3].ind_type = -1;
    sqlhv[3].ind_el_size = 0;
    sqlhv[3].indicator = NULL;
    sqlhv[3].ptr_size = -1;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 267 "Goldilocks.gc"


  CHECK_ERROR;

  return 0 ;
}  

int Goldilocks :: CloseRequest  (uint64 aNo, char* aCoin )
{

  /* EXEC SQL BEGIN DECLARE SECTION ; */
#line 277 "Goldilocks.gc"

  uint64 sNo;
  char   *sCoin; 
  /* EXEC SQL END   DECLARE SECTION ; */
#line 280 "Goldilocks.gc"


  sNo = aNo ;
  sCoin = aCoin ;

  /* EXEC SQL UPDATE FILL_REQUEST 
           SET AVAIL_QTY = 0, PROCESS = 2 
           WHERE COIN = :sCoin AND TICKET_NO = :sNo  */
{
    sqlargs_t sqlargs;
#line 1205 "Goldilocks.cc"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 7;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = (char *)"UPDATE FILL_REQUEST \n"
"           SET AVAIL_QTY = 0, PROCESS = 2 \n"
"           WHERE COIN = :sCoin AND TICKET_NO = :sNo \n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.iters = 0;
    sqlhv_t sqlhv[2];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 2;
    sqlhv[0].io_type = 0;
    sqlhv[0].data_type = 13;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = 0;
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(sCoin);
    sqlhv[0].value = (void *)sCoin;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].ptr_size = -1;
    sqlhv[1].io_type = 0;
    sqlhv[1].data_type = 6;
    sqlhv[1].arr_size = 0;
    sqlhv[1].buflen = sizeof(sNo);
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(sNo);
    sqlhv[1].value = (void *)&sNo;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].ptr_size = -1;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 287 "Goldilocks.gc"


  CHECK_ERROR;
  
  return 0 ;
}

int Goldilocks :: BuildFill (char *aCoin, 
                             uint64 aPrice, 
                             char * aQty, 
                             uint64 aReqID, 
                             uint64 aOppositeID ) 
{
  /* EXEC SQL BEGIN DECLARE SECTION ; */
#line 300 "Goldilocks.gc"


  uint64 sPrice;
  char   *sCoin ;
  char   sQty[MAX_FLOATING_LENGTH]; 
  uint64 sReqID;
  uint64 sOppositeID; 

  /* EXEC SQL END   DECLARE SECTION ; */
#line 308 "Goldilocks.gc"



  sCoin = aCoin;
  sPrice = aPrice ;
  strncpy ( sQty, aQty, MAX_FLOATING_LENGTH ) ;
  sReqID = aReqID; 
  sOppositeID = aOppositeID;


  /* EXEC SQL INSERT INTO FILL_HISTORY 
      (COIN, FILL_TIME, PRICE , QTY, TICKET_NO, OPPOSITE_TICKET_NO ) 
      VALUES 
      (:sCoin, SYSTIMESTAMP, :sPrice, :sQty, :sReqID, :sOppositeID )  */
{
    sqlargs_t sqlargs;
#line 1303 "Goldilocks.cc"
    sqlargs.sqltype    = 0;
    sqlargs.sql_ca     = NULL;
    sqlargs.conn       = NULL;
    sqlargs.sql_state  = NULL;
    sqlargs.sqlstmt    = NULL;
    sqlargs.sqlfn      = NULL;
    sqlargs.sqlln      = 0;
    sqlargs.sqlcursor  = NULL;
    sqlargs.sqlfetch   = NULL;
    sqlargs.hvc        = 0;
    sqlargs.sqlhv      = NULL;
    sqlargs.dynusing   = NULL;
    sqlargs.dyninto    = NULL;
    sqlargs.option     = (void *)&gZlpOption;
    sqlargs.sql_ca = &sqlca;
    sqlargs.sql_state = SQLSTATE;
    sqlargs.sqltype = 6;
    sqlargs.sqlfn = (char *)__FILE__;
    sqlargs.sqlln = __LINE__;
    sqlargs.sqlstmt = (char *)"INSERT INTO FILL_HISTORY \n"
"      (COIN, FILL_TIME, PRICE , QTY, TICKET_NO, OPPOSITE_TICKET_NO ) \n"
"      VALUES \n"
"      (:sCoin, SYSTIMESTAMP, :sPrice, :sQty, :sReqID, :sOppositeID ) \n"
;
    sqlargs.atomic = 0;
    sqlargs.unsafenull = 0;
    sqlargs.iters = 0;
    sqlhv_t sqlhv[5];
    sqlargs.sqlhv = sqlhv;
    sqlargs.hvc = 5;
    sqlhv[0].io_type = 0;
    sqlhv[0].data_type = 13;
    sqlhv[0].arr_size = 0;
    sqlhv[0].buflen = 0;
    sqlhv[0].precision = 0;
    sqlhv[0].scale = 0;
    sqlhv[0].el_size = sizeof(sCoin);
    sqlhv[0].value = (void *)sCoin;
    sqlhv[0].ind_type = -1;
    sqlhv[0].ind_el_size = 0;
    sqlhv[0].indicator = NULL;
    sqlhv[0].ptr_size = -1;
    sqlhv[1].io_type = 0;
    sqlhv[1].data_type = 6;
    sqlhv[1].arr_size = 0;
    sqlhv[1].buflen = sizeof(sPrice);
    sqlhv[1].precision = 0;
    sqlhv[1].scale = 0;
    sqlhv[1].el_size = sizeof(sPrice);
    sqlhv[1].value = (void *)&sPrice;
    sqlhv[1].ind_type = -1;
    sqlhv[1].ind_el_size = 0;
    sqlhv[1].indicator = NULL;
    sqlhv[1].ptr_size = -1;
    sqlhv[2].io_type = 0;
    sqlhv[2].data_type = 13;
    sqlhv[2].arr_size = 0;
    sqlhv[2].buflen = MAX_FLOATING_LENGTH;
    sqlhv[2].precision = 0;
    sqlhv[2].scale = 0;
    sqlhv[2].el_size = sizeof(sQty);
    sqlhv[2].value = (void *)sQty;
    sqlhv[2].ind_type = -1;
    sqlhv[2].ind_el_size = 0;
    sqlhv[2].indicator = NULL;
    sqlhv[2].ptr_size = -1;
    sqlhv[3].io_type = 0;
    sqlhv[3].data_type = 6;
    sqlhv[3].arr_size = 0;
    sqlhv[3].buflen = sizeof(sReqID);
    sqlhv[3].precision = 0;
    sqlhv[3].scale = 0;
    sqlhv[3].el_size = sizeof(sReqID);
    sqlhv[3].value = (void *)&sReqID;
    sqlhv[3].ind_type = -1;
    sqlhv[3].ind_el_size = 0;
    sqlhv[3].indicator = NULL;
    sqlhv[3].ptr_size = -1;
    sqlhv[4].io_type = 0;
    sqlhv[4].data_type = 6;
    sqlhv[4].arr_size = 0;
    sqlhv[4].buflen = sizeof(sOppositeID);
    sqlhv[4].precision = 0;
    sqlhv[4].scale = 0;
    sqlhv[4].el_size = sizeof(sOppositeID);
    sqlhv[4].value = (void *)&sOppositeID;
    sqlhv[4].ind_type = -1;
    sqlhv[4].ind_el_size = 0;
    sqlhv[4].indicator = NULL;
    sqlhv[4].ptr_size = -1;
    DBESQL_Execute(NULL, &sqlargs);
}
#line 321 "Goldilocks.gc"


  CHECK_ERROR;


  
  return 0 ;

}

int Goldilocks :: GetOfferStatus (OfferVector &aVector )
{
  /*

  EXEC SQL BEGIN DECLARE SECTION ;
  Offer sOffer; 
  char *sQuery; 
  EXEC SQL END  DECLARE SECTION ;

  memset (&sOffer, 0x00, sizeof(Offer )) ;
  sQuery = mQueryMap ["SELECT_STATUS"] ;

  EXEC SQL PREPARE SELECT_STMT2 FROM :sQuery ; 
  CHECK_ERROR;
  
  EXEC SQL DECLARE SELECT_CURSOR2 CURSOR FOR SELECT_STMT2 ; 
  CHECK_ERROR;
  
  EXEC SQL OPEN SELECT_CURSOR2  ;
  CHECK_ERROR;
  

  while ( true ) 
  {
    EXEC SQL FETCH NEXT SELECT_CURSOR2 INTO :sOffer; 
    if ( sqlca.sqlcode == SQL_NO_DATA ) 
    {
      break; 
    } 
    aVector.push_back ( sOffer ) ;
  }

  EXEC SQL CLOSE SELECT_CURSOR2 ; 
  CHECK_ERROR;
  */

  return 0; 
} 



}

