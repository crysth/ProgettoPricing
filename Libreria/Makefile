LIB=  yield_curve.o yield_curve_flat.o yield_curve_term_struct.o price.o currency.o eq_description.o vol_std.o volatility.o time.o rand_gen_root.o rand_gen.o process.o deltatime.o eq_option.o eq_price.o eq_pricer.o eq_pricer_montecarlo.o eq_process.o n_rand.o option.o path.o timestruct.o errorlist.o eq_op_performance_with_corridor.o statistica.o stima_montecarlo.o eq_process_lognormal_eulero.o eq_process_lognormal_esatto.o eq_process_lognormal_binary.o pricing.o eq_op_plainvanilla.o eq_op_w.o
CC=g++
OPT= -O3 -Wall
MAIN=main

INCS = `root-config --cflags`
LIBS = `root-config --libs`


main : ${LIB} ${MAIN}.cpp
	${CC} ${OPT} ${LIB} ${MAIN}.cpp -o ${MAIN}.x ${INCS} ${LIBS}

yield_curve.o : yield_curve.cpp yield_curve.hpp
	${CC} ${OPT} -c yield_curve.cpp

yield_curve_flat.o : yield_curve_flat.cpp yield_curve_flat.hpp
	${CC} ${OPT} -c yield_curve_flat.cpp

yield_curve_term_struct.o : yield_curve_term_struct.cpp yield_curve_term_struct.hpp
	${CC} ${OPT} -c yield_curve_term_struct.cpp

price.o : price.cpp price.hpp
	${CC} ${OPT} -c price.cpp
	
eq_price.o : eq_price.cpp eq_price.hpp
	${CC} ${OPT} -c eq_price.cpp	
	
currency.o : currency.cpp currency.hpp
	${CC} ${OPT} -c currency.cpp

eq_description.o : eq_description.cpp eq_description.hpp
	${CC} ${OPT} -c eq_description.cpp
	
vol_std.o : vol_std.cpp vol_std.hpp
	${CC} ${OPT} -c vol_std.cpp		
	
volatility.o : volatility.cpp volatility.hpp
	${CC} ${OPT} -c volatility.cpp	

time.o : time.cpp time.hpp
	${CC} ${OPT} -c time.cpp 

deltatime.o : deltatime.cpp deltatime.hpp
	${CC} ${OPT} -c deltatime.cpp

option.o : option.cpp option.hpp
	${CC} ${OPT} -c option.cpp

rand_gen_root.o : rand_gen_root.cpp rand_gen_root.hpp
	${CC} ${OPT} -c rand_gen_root.cpp ${INCS}

rand_gen.o : rand_gen.cpp rand_gen.hpp
	${CC} ${OPT} -c rand_gen.cpp

process.o : process.cpp process.hpp
	${CC} ${OPT} -c process.cpp

eq_option.o : eq_option.cpp eq_option.hpp
	${CC} ${OPT} -c eq_option.cpp ${INCS}

n_rand.o : n_rand.cpp n_rand.hpp
	${CC} ${OPT} -c n_rand.cpp

path.o : path.cpp path.hpp
	${CC} ${OPT} -c path.cpp ${INCS}

eq_pricer.o : eq_pricer.cpp eq_pricer.hpp
	${CC} ${OPT} -c eq_pricer.cpp ${INCS}

eq_pricer_montecarlo.o : eq_pricer_montecarlo.cpp eq_pricer_montecarlo.hpp
	${CC} ${OPT} -c eq_pricer_montecarlo.cpp ${INCS}

eq_process.o : eq_process.cpp eq_process.hpp
	${CC} ${OPT} -c eq_process.cpp ${INCS}

timestruct.o : timestruct.cpp timestruct.hpp
	${CC} ${OPT} -c timestruct.cpp 

errorlist.o : errorlist.cpp errorlist.hpp
	${CC} ${OPT} -c errorlist.cpp

eq_op_performance_with_corridor.o : eq_op_performance_with_corridor.cpp eq_op_performance_with_corridor.hpp
	${CC} ${OPT} -c eq_op_performance_with_corridor.cpp ${INCS}

statistica.o : statistica.cpp statistica.hpp
	${CC} ${OPT} -c statistica.cpp ${INCS}

stima_montecarlo.o : stima_montecarlo.cpp stima_montecarlo.hpp
	${CC} ${OPT} -c stima_montecarlo.cpp 

eq_process_lognormal_eulero.o : eq_process_lognormal_eulero.cpp eq_process_lognormal_eulero.hpp
	${CC} ${OPT} -c eq_process_lognormal_eulero.cpp ${INCS}

eq_process_lognormal_esatto.o : eq_process_lognormal_esatto.cpp eq_process_lognormal_esatto.hpp
	${CC} ${OPT} -c eq_process_lognormal_esatto.cpp ${INCS}

eq_process_lognormal_binary.o : eq_process_lognormal_binary.cpp eq_process_lognormal_binary.hpp
	${CC} ${OPT} -c eq_process_lognormal_binary.cpp ${INCS}

pricing.o : pricing.cpp pricing.hpp
	${CC} ${OPT} -c pricing.cpp ${INCS}

eq_op_plainvanilla.o : eq_op_plainvanilla.cpp eq_op_plainvanilla.hpp
	${CC} ${OPT} -c eq_op_plainvanilla.cpp ${INCS}

eq_op_w.o : eq_op_w.cpp eq_op_w.hpp
	${CC} ${OPT} -c eq_op_w.cpp ${INCS}

clean :
	rm -f *.o *.x *~ *.dat
