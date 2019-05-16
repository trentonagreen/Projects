mizzo: driver.o conveyorbelt.o producer.o consumer.o
	cc driver.o conveyorbelt.o producer.o consumer.o -o mizzo -lpthread -lrt 

driver.o: driver.c conveyorbelt.h producer.h consumer.h
	cc -c driver.c

conveyorbelt.o: conveyorbelt.c conveyorbelt.h
	cc -c conveyorbelt.c

producer.o: producer.c producer.h
	cc -c producer.c

consumer.o: consumer.c consumer.h
	cc -c consumer.c	

clean:
	rm *.o
