Proj1: main.o App.o Courier.o CourierList.o Order.o OrderList.o
	g++ main.o App.o Courier.o CourierList.o Order.o OrderList.o -o proj1

main.o: main.cpp
	g++ -c main.cpp

App.o: App.cpp
	g++ -c App.cpp

Courier.o: Courier.cpp
	g++ -c Courier.cpp

CourierList.o: CourierList.cpp
	g++ -c CourierList.cpp

Order.o: Order.cpp
	g++ -c Order.cpp

OrderList.o: OrderList.cpp
	g++ -c OrderList.cpp

clean:
	rm *.o proj1