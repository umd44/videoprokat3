CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRCS = Client.cpp VideoCarrier.cpp FinancialCalculator.cpp Rental.cpp \
       Catalog.cpp RentalManager.cpp ReportGenerator.cpp \
       PremiumClient.cpp DVDCarrier.cpp BluRayCarrier.cpp PaymentProcessor.cpp

MAIN_SRCS = $(SRCS) videoprokat.cpp

MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)

all: videoprokat InheritanceDemo

videoprokat: $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

InheritanceDemo: $(SRCS) ../demos/InheritanceDemo.cpp
	cd .. && $(CXX) $(CXXFLAGS) -I videoprokat videoprokat/Client.cpp videoprokat/VideoCarrier.cpp videoprokat/FinancialCalculator.cpp videoprokat/Rental.cpp videoprokat/Catalog.cpp videoprokat/RentalManager.cpp videoprokat/ReportGenerator.cpp videoprokat/PremiumClient.cpp videoprokat/DVDCarrier.cpp videoprokat/BluRayCarrier.cpp videoprokat/PaymentProcessor.cpp demos/InheritanceDemo.cpp -o demos/InheritanceDemo

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o videoprokat ../demos/InheritanceDemo

.PHONY: all clean
