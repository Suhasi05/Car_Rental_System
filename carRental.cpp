#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
class Car{
    string carId;
    string brand;
    string model;
    double basePricePerDay;
    bool isAvailable;

    public:
    Car(string carId, string brand, string model, double basePricePerDay){
        this->carId = carId;
        this->brand = brand;
        this->model = model;
        this->basePricePerDay = basePricePerDay;
        this->isAvailable  = true;
    }
    string getCarId() {
        return carId;
    }
    string getModel() {
        return model;
    }
    string getBrand() {
        return brand;
    }
    double calculatePrice(int rentalDays) {
        return basePricePerDay * rentalDays;
    }
    void rent() {
        isAvailable = false;
    }
    void returnCar() {
        isAvailable = true;
    }
    bool IsAvailable() {
        return isAvailable;
    }
};
class Customer {
    string customerId;
    string name;

    public:
    Customer(string customerId, string name) {
        this->customerId = customerId;
        this->name = name;
    }
    string getCustomerId() {
        return customerId;
    }
    string getName() {
        return name;
    }
};
class Rental {
    Car* car;
    Customer* customer;
    int days;

    public:
    Rental(Car* car, Customer* customer, int days) {
        this->car = car;
        this->customer = customer;
        this->days = days;
    }
    Car* getCar() {
        return car;
    }
    Customer* getCustomer() {
        return customer;
    }
    int getDays() {
        return days;
    }
};

class CarRentalSystem {
    vector<Car*> cars;
    vector<Customer*> customers;
    vector<Rental*> rentals;
    public:
    CarRentalSystem() {}

     void addCar(Car* car) {
        cars.push_back(car);
     }
     void addCustomer(Customer* customer) {
        customers.push_back(customer);
     }
     void rentCar(Car* car, Customer* customer, int days) {
        if(car->IsAvailable()) {
            car->rent();
            rentals.push_back(new Rental(car, customer, days));
        }
        else {
            cout<<"Car is not available for rent\n";
        }
     }
     void returnCar(Car* car) {
        car->returnCar();
        Rental* rentalToRemove = nullptr;
        Customer* customer = nullptr;
        for (Rental* rental : rentals) {
            if (rental->getCar() == car) {
                rentalToRemove = rental;
                customer = rental->getCustomer();
                break;
            }
        }
        if(rentalToRemove != nullptr) {
            rentals.erase(remove(rentals.begin(), rentals.end(), rentalToRemove), rentals.end());
             cout<<"Car returned successfully by "<<customer->getName();
        }
        else {
            cout<<"Car was not rented";
        }
     }
    void menu()
    {
        int choice;
        string customerName;
        string carId;
        int rentalDays;
        string confirm;
     while(1) {
        cout<<"\n---- Car Rental System ----\n";
        cout<<"1. Rent a Car\n";
        cout<<"2. Return a Car\n";
        cout<<"3. Exit\n";
        cout<<"\nEnter your Choice : ";
        cin>>choice;
        
        switch (choice)
        {
        case 1:
        {
            cout<<"\n-- Rent a Car --\n";
            cout<<"Enter your name : ";
            cin>>customerName;
            cout<<"\nAvailable Cars : \n"; 
            for(Car* car : cars) {
                if(car->IsAvailable()) {
                    cout<<car->getCarId() <<" - "<< car->getBrand()<<" "<<car->getModel()<<endl;
                }
            }
            cout<<"\nEnter the car ID you want to rent : ";
            cin>>carId;
            cout<<"Enter the number of days for rental : ";
            cin>>rentalDays;

            Customer* newCustomer = new Customer("CUS" + to_string(customers.size()+1), customerName);
            addCustomer(newCustomer);

            Car* selectedCar = nullptr;
            for(Car* car : cars) {
                if(car->getCarId() == carId && car->IsAvailable()) {
                    selectedCar = car;
                    break;
                }
            }
            cout<<endl;
            if(selectedCar != nullptr) {
                double totalPrice = selectedCar->calculatePrice(rentalDays);
                cout<<"\n-- Rental Information --\n";
                cout<<"Customer ID : "<<newCustomer->getCustomerId();
                cout<<"\nCustomer Name : "<<newCustomer->getName();
                cout<<"\nCar : "<<selectedCar->getBrand()<<" "<<selectedCar->getModel();
                cout<<"\nRental Days : "<<rentalDays;
                cout<<"\nTotal Price : "<<totalPrice;

                cout<<"\n\nConfirm rental (Y/N) : ";
                cin>>confirm;
                if(confirm == "Y" || confirm == "y") {
                    rentCar(selectedCar, newCustomer, rentalDays);
                    cout<<"\nCar rented successfully to " << newCustomer->getName()<<endl;
                }
                else {
                    cout<<"\nRental canceled\n";
                }
            }
            else {
                cout<<"Invalid car selection or car is not available for rent";
            }
            break;
        }
        case 2: {
        cout<<"\n-- Return a Car --\n";
        cout<<"Enter the car ID you want to return : ";
        cin>>carId;

        Car* carToReturn = nullptr;
        for(Car* car : cars) {
            if(car->getCarId() == carId && !car->IsAvailable()) {
                carToReturn = car;
                break;
            }
        } 
        if(carToReturn != nullptr) {
            Customer* customer = nullptr;
        for(Rental* rental : rentals) {
            if(rental->getCar() == carToReturn) {
                customer = rental->getCustomer();
                break;
            }
        }
         if(customer != nullptr) {
            returnCar(carToReturn);
         }
         else {
            cout<<"Car was not rented or rental information is missing\n";
         }
        }
        else {
            cout<<"Invalid car ID or car is not rented\n";
        }
            break;
        }
         
        case 3: {
            exit(0);
        }
        default : 
        cout<<"\nEnter Valid Choice\n";
        }
     }
    }
};
int main()
{
    CarRentalSystem rentalSystem;

    Car car1("C001", "Toyota", "Camry", 600);
    Car car2("C002", "Honda", "Accord", 700);
    Car car3("C003", "Mahindra", "Thar", 1500);
    Car car4("C004", "Maruti Suzuki", "Swift", 500);
    Car car5("C005", "Audi", "Q3", 1000);

    rentalSystem.addCar(&car1);
    rentalSystem.addCar(&car2);
    rentalSystem.addCar(&car3);
    rentalSystem.addCar(&car4);
    rentalSystem.addCar(&car5);

    rentalSystem.menu();
    cout<<"\nThank you for using the car Rental System!\n";
    return 0;
}