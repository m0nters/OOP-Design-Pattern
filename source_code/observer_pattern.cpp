#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Subscriber interface
class Subscriber {
public:
    virtual void update(float temp, float humidity, float pressure) = 0;
};

// Publisher
class WeatherStation {
private:
    vector<Subscriber*> subscribers;
    float temperature;
    float humidity;
    float pressure;

public:
    void registerSubscriber(Subscriber* s) {
        subscribers.push_back(s);
    }

    void removeSubscriber(Subscriber* s) {
        auto it = find(subscribers.begin(), subscribers.end(), s);
        if (it != subscribers.end()) {
            subscribers.erase(it);
        }
    }

    void notifySubscribers() {
        for (Subscriber* subscriber : subscribers) {
            subscriber->update(temperature, humidity, pressure);
        }
    }

    void measurementsChanged() {
        notifySubscribers();
    }

    void setMeasurements(float temperature, float humidity, float pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        measurementsChanged();
    }
};

// Concrete Subscriber
class SmartPhoneDisplay : public Subscriber {
private:
    WeatherStation* weatherStation;
    float temperature;
    float humidity;

public:
    SmartPhoneDisplay(WeatherStation* weatherStation) {
        this->weatherStation = weatherStation;
        this->weatherStation->registerSubscriber(this);
    }

    void update(float temperature, float humidity, float pressure) override {
        this->temperature = temperature;
        this->humidity = humidity;
        display();
    }

    void display() {
        cout << "SmartPhone Display: Temperature is " << temperature << "F, Humidity is " << humidity << "%" << endl;
    }
};

class WeatherWebsite : public Subscriber {
private:
    WeatherStation* weatherStation;
    float temperature;
    float humidity;
    float pressure;

public:
    WeatherWebsite(WeatherStation* weatherStation) {
        this->weatherStation = weatherStation;
        this->weatherStation->registerSubscriber(this);
    }

    void update(float temperature, float humidity, float pressure) override {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        display();
    }

    void display() {
        cout << "Weather Website Display: Temperature is " << temperature << "F, Humidity is " << humidity << "%, Pressure is " << pressure << endl;
    }
};

int main() {
    WeatherStation ws;

    SmartPhoneDisplay spd(&ws);
    WeatherWebsite ww(&ws);

    ws.setMeasurements(80, 65, 30.4f);
    ws.setMeasurements(82, 70, 29.2f);
    ws.setMeasurements(78, 90, 29.2f);

    ws.removeSubscriber(&spd);
    ws.setMeasurements(75, 60, 28.5f);

    return 0;
}
