
DROP TABLE FILL_REQUEST ; 
CREATE TABLE FILL_REQUEST 
(
	COIN     VARCHAR(100) NOT NULL, 
	TICKET_NO   NUMBER(30,0) NOT NULL, 
	REQ_TIME TIMESTAMP NOT NULL , 
	POSITION NUMBER ( 1 ) NOT NULL,
	PRICE    NUMBER ( 30, 0) NOT NULL,  
	REQ_QTY  NUMBER (30,18) NOT NULL, 
	AVAIL_QTY NUMBER(30,18) NOT NULL, 
	PROCESS   NUMBER(1) NOT NULL, 
	ORDER_TYPE NUMBER(1) NOT NULL, 
	ORDER_NO   NUMBER(30,0) NOT NULL
) SHARDING BY LIST ( COIN ) 
SHARD S1 VALUES IN ( 'BTC') AT CLUSTER GROUP G1 , 
SHARD S2 VALUES IN ( 'ETH') AT CLUSTER GROUP G2, 
SHARD S3 VALUES IN ( 'ETC') AT CLUSTER GROUP G1, 
SHARD S4 VALUES IN ( 'XRP') AT CLUSTER GROUP G2, 
SHARD S5 VALUES IN ( 'LTC') AT CLUSTER GROUP G1, 
SHARD S6 VALUES IN ( DEFAULT) AT CLUSTER GROUP G2 
;


ALTER TABLE FILL_REQUEST ADD PRIMARY KEY ( REQ_TIME);
CREATE INDEX IDX_FILL_REQUEST_ASK ON FILL_REQUEST ( POSITION, PRICE ASC , REQ_TIME );
CREATE INDEX IDX_FILL_REQUEST_BID ON FILL_REQUEST (  POSITION, PRICE DESC , REQ_TIME );
CREATE INDEX IDX_TICKET ON FILL_REQUEST (  TICKET_NO );


DROP SEQUENCE TICKET_SEQ; 
CREATE SEQUENCE TICKET_SEQ START WITH 1 CACHE 100 ; 

DROP TABLE FILL_HISTORY ; 
CREATE TABLE FILL_HISTORY 
(
	COIN     VARCHAR(100) NOT NULL, 
	FILL_TIME   TIMESTAMP NOT NULL, 
	PRICE       NUMBER (30,0) NOT NULL, 
	QTY         NUMBER (30,18) NOT NULL, 
	TICKET_NO      NUMBER (30, 0) NOT NULL, 
	OPPOSITE_TICKET_NO NUMBER ( 30, 0) NOT NULL 
) SHARDING BY LIST ( COIN ) 
SHARD S1 VALUES IN ( 'BTC') AT CLUSTER GROUP G1 , 
SHARD S2 VALUES IN ( 'ETH') AT CLUSTER GROUP G2, 
SHARD S3 VALUES IN ( 'ETC') AT CLUSTER GROUP G1, 
SHARD S4 VALUES IN ( 'XRP') AT CLUSTER GROUP G2, 
SHARD S5 VALUES IN ( 'LTC') AT CLUSTER GROUP G1, 
SHARD S6 VALUES IN ( DEFAULT) AT CLUSTER GROUP G2 
;
ALTER TABLE FILL_HISTORY ADD PRIMARY KEY ( COIN, FILL_TIME);

