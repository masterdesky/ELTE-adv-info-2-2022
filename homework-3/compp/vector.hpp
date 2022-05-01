

class vector3d {
    private:
        double x, y, z;

    public:
        vector3d(double xi, double yi, double zi);  // Constructor
        vector3d(vector3d const &v);                // Copy constructor
        ~vector3d();                                // Destructor

        // Overloading arithmetic operators
        friend vector3d operator+(vector3d const &v1, vector3d const &v2);
        vector3d& operator+=(vector3d const& v);

        friend vector3d operator-(vector3d const &v1, vector3d const &v2);
        vector3d& operator-=(vector3d const& v);

        friend double operator*(vector3d const &v1, vector3d const &v2);
        double operator*=(vector3d const &v);

        friend vector3d operator*(vector3d const &v, double const &c);
        friend vector3d operator*(double const &c, vector3d const &v);
        vector3d& operator*=(double const &c);

        friend vector3d operator/(vector3d const &v, double const &c);
        friend vector3d operator/(double const &c, vector3d const &v);
        vector3d& operator/=(double const &c);

        // Overloading IO operators
        friend std::ostream& operator<<(std::ostream& o, vector3d const& v);
        friend std::istream& operator>>(std::istream& i, vector3d& v);
};