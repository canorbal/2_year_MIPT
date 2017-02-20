class Vector
{
    double x,y,z; // по дефолту закрыты
    public:
        double get_x();
        double get_y();
        double get_z();
        void set_x(double x);
        void set_y(double y);
        void set_z(double z);
        Vector plus(Vector A);
        Vector operator + (Vector A);
        Vector operator - (Vector A);
        double operator * (Vector A);
        Vector operator * (double k);
        Vector(double x, double y, double z);
        Vector mul(double k);
        double mul(Vector A);
        
    private:

};


