
#include <iostream>
#include <string>
using namespace std;
class Engine{
    private:
        int m_EngineCapacity;
        int m_HorsePower;
        bool m_EngineRunning;
    public:
        Engine(int EngineCapacity=2000, int HorsePower=200){
            m_EngineCapacity=EngineCapacity;
            m_HorsePower=HorsePower;
            m_EngineRunning=false;
        }
        bool EngineStart(){
            if(!m_EngineRunning){
                m_EngineRunning=true;
            }
            return true;
        };
        bool EngineStop(){
            if(!m_EngineRunning){
                m_EngineRunning=false;
            }
            return true;
        };
        bool get_EngineStatus(){
            return m_EngineRunning;
        };
};
class Fueltank{
    private:
        int m_FueltankCapacity;
        int m_Gas_grade;
    public:
        Fueltank(int FueltankCapacity=3000, int Gas=98){
            m_FueltankCapacity=FueltankCapacity;
            m_Gas_grade=Gas;
        }
        int fuel_up(int v ,int gas){
            if ((v<=m_FueltankCapacity) && (gas==m_Gas_grade)){
                cout << "fuel_up: "<<v<<" Gas_grade: "<<gas<<endl;
               
            }else{
                if (v>m_FueltankCapacity){
                    cout<<"Error: FueltankCapacity: "<<m_FueltankCapacity;
                    cout<< " but fuel up: "<< v<<endl;
                }
                if (gas!=m_Gas_grade){
                    cout<<"Error: Gas_grade: "<<gas;
                    cout<< " Correct Gas_grade: "<< m_Gas_grade<<endl;
                }
            }return 0;
           
        }
        int set_Gas_grade(int Gas_grade){
            m_Gas_grade=Gas_grade;
            cout << "Set Gas_grade: " <<Gas_grade<<endl;
            return m_Gas_grade;
        }
        int get_Gas_grade(){
            return m_Gas_grade ;
        };
       
};
class Car{
    protected:
    string m_DriveMode;
    private:
    Engine m_Engine;
    Fueltank m_Fueltank;
    int m_MaxSeating;
    int m_price;
    int m_base;
    void m_UpdatePrice(int base=50000){
        m_price=m_MaxSeating*base;
    }
    public:
    string m_brand;
    string m_model;
    int m_year;
   
    Car(string x,string y,int z,int s){
        m_brand=x;
        m_model=y;
        m_year=z;
        m_MaxSeating=s;
        m_UpdatePrice();
        //m_DriveMode="No-wheel";
    }
    int get_MaxSeating(){
        return m_MaxSeating;
    }
    int get_Price(){
        return m_price;
    }
    //void set_base(int n){}
    string get_brand(){
        return m_brand;
    }
    string get_DriveMode(){
        return m_DriveMode;
    }
    bool get_EngineStatus(){
        return m_Engine.get_EngineStatus();
    }
    bool startEngine(){
        return m_Engine.EngineStart();
    };
    bool stopEngine(){
        return m_Engine.EngineStop();
    };
    int get_Gas_grade(){
        return m_Fueltank.get_Gas_grade();
    };
    int set_Gas_grade(int gas=98){
        return m_Fueltank.set_Gas_grade(gas);
    };
    int fuel_up(int v,int gas=98){
        return m_Fueltank.fuel_up(v,gas);
    };
};
class BMW_Car : public Car{
    //private:
   // string m_DriveMode;
   
    public:
    BMW_Car(string y, int z, int s): Car("BMW",y,z,s){
        cout << "Constructing BMW_Car\n";
        m_DriveMode="Rear-wheel";
    }
   
    string get_DriveMode(){
        return m_DriveMode;
    }
};

class AUDI_Car : public Car{
    //private:
    //string m_DriveMode;
    public:
    AUDI_Car(string y, int z, int s):Car("AUDI",y,z,s){
        cout << "Constructing AUDI_Car\n";
        m_DriveMode="Front-wheel";
    }
   
    string get_DriveMode(){
        return m_DriveMode;
    }
};

class BENZ_Car : public Car{
    //private:
    //string m_DriveMode;
   
    public:
    BENZ_Car(string y, int z, int s):Car("BENZ",y,z,s){
        cout << "Constructing BENZ_Car\n";
        m_DriveMode="Front-wheel";
    }
   
    string get_DriveMode(){
        return m_DriveMode;
    }
};
int main(){
   
    //BMW_Car car_1("X5", 2023, 6);
    //cout << car_1.m_brand;
    //cout << " : Drive Mode = " <<car_1.get_DriveMode() <<endl;
    //cout << " : EngineStatus= " <<car_1.get_EngineStatus() <<endl;
    AUDI_Car car_2("A1", 2021, 2);
    car_2.startEngine();
    cout << car_2.get_brand()<<" : Gas_grade= " << car_2.get_Gas_grade() <<endl;
    car_2.set_Gas_grade(95);
    cout << car_2.get_brand()<<" : Gas_grade= " << car_2.get_Gas_grade() <<endl;
    car_2.fuel_up(30000,99);
    //cout << " : Drive Mode = " <<car_2.get_DriveMode() <<endl;
    //cout << " : EngineStatus= " <<car_2.get_EngineStatus() <<endl;
    //BENZ_Car car_3("E300", 2023, 6);
    //cout << car_3.m_brand;
    //cout << " : Drive Mode = " <<car_3.get_DriveMode() <<endl;
    //cout << " : EngineStatus= " <<car_3.get_EngineStatus() <<endl;
    return 0;
}
