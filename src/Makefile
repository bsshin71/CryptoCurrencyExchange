
INC=-I. -I${GOLDILOCKS_HOME}/include 
LIB_DIR=-L. -L${GOLDILOCKS_HOME}/lib
LIBS=-lgoldilocksesql -lgoldilocksc  -lpthread -lm  -ldl -lrt
CXXFLAGS=-g -O0 -W -Wall  --std=c++11 
OBJS=FillSimulator.o Goldilocks.o DBStrategy.o

all : 
	gpec Goldilocks.gc --output Goldilocks.cc
	${CXX} ${CXXFLAGS} -c ExchangeException.cc ${INC}
	${CXX} ${CXXFLAGS} -c Exchange.cc ${INC}
	${CXX} ${CXXFLAGS} -c DB.cc ${INC}
	${CXX} ${CXXFLAGS} -c Goldilocks.cc ${INC}
	${CXX} ${CXXFLAGS} -c BCMath.cc ${INC}
	${CXX} ${CXXFLAGS} -c BaseExchange.cc ${INC}
	${CXX} ${CXXFLAGS} -c PlaceOrder.cc ${INC}
	${CXX} ${CXXFLAGS} -o PlaceOrder.exe  DB.o Exchange.o Goldilocks.o BaseExchange.o PlaceOrder.o BCMath.o ${INC} ${LIBS} ${LIB_DIR}


	
	

clean : 
	rm -f *.o Goldilocks.cc UnitTest *.out  PlaceOrder.exe ExceptionTest PTest
