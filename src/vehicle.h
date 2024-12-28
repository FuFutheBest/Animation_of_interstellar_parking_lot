#ifndef VECHICLE_H
#define VECHICLE_H
class vehicle {
    public:
        float get_price(float arrival_time, float time_now);
        int get_type();
        void set_type(int type);
        float get_arrival_time();
        void set_arrival_time(float arrival_time);
        void print_vehicle();
    private:
        int type; // 0 stand for vans, 1 for cars, 2 for motorcycles, 3 for bicycles
        float arrival_time;
};

class van : public vehicle {
    public:
        van();
        van(float arrival_time);
};

class car : public vehicle {
    public:
        car();
        car(float arrival_time);
};

class motorcycle : public vehicle {
    public:
        motorcycle();
        motorcycle(float arrival_time);
};

class bicycle : public vehicle {
    public:
        bicycle();
        bicycle(float arrival_time);
};

vehicle generate_vehicle( float arrival_time ); // generate a random vehicle

#endif
