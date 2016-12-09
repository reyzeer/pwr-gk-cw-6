/// Laboratorium: Grafika Komputerowa
/// Prowadzący: Dr inż. Marek Woda
/// Cwiczenie 4
/// Zbigniew Czarnecki 209909

#include "common.h"

const float PI = 3.14159265359;

class Egg
{

private:

    /// Points in egg
    float *** matrix;

    /// Colors for all points in egg
    float *** colors;

    /// Normal vectors for all points in egg
    float *** normalVector;

    /// Generate random color for egg
    bool colorAvailable = false;

    /// IS egg render
    bool build = false;

    float distance;

    /// Generuje "dwu"wymiarową tablicę punktów XYZ
    void prepareMatrix();

    /// Generate array for normal vector
    void prepareNormalVector();

    float x(float u, float v);
    float y(float u, float v);
    float z(float u, float v);

    void generateNormalVector();

    float xu(float u, float v);
    float xv(float u, float v);

    float yu(float u);
    float yv(float v);

    float zu(float u, float v);
    float zv(float u, float v);

    float normalVectorCoordinateX(float u, float v);
    float normalVectorCoordinateY(float u, float v);
    float normalVectorCoordinateZ(float u, float v);

    /// Vector for side of egg
    ///
    /// \param i Row in matrix
    /// \param j Col in matrix
    /// \param x normal vectro coordinate x
    /// \param y normal vectro coordinate y
    /// \param z normal vectro coordinate z
    void vector4SideFront(int i, int j, float x, float y, float z);

    /// Vector for side of egg
    ///
    /// \param i Row in matrix
    /// \param j Col in matrix
    /// \param x normal vectro coordinate x
    /// \param y normal vectro coordinate y
    /// \param z normal vectro coordinate z
    void vector4SideBack(int i, int j, float x, float y, float z);

    /// Vector for top of egg
    ///
    /// \param i Row in matrix
    /// \param j Col in matrix
    /// \param x normal vectro coordinate x
    /// \param y normal vectro coordinate y
    /// \param z normal vectro coordinate z
    void vector4Top(int i, int j, float x, float y, float z);

    /// Vector for bottom of egg
    ///
    /// \param i Row in matrix
    /// \param j Col in matrix
    /// \param x normal vectro coordinate x
    /// \param y normal vectro coordinate y
    /// \param z normal vectro coordinate z
    void vector4Bottom(int i, int j, float x, float y, float z);

    /// Deleted 3D array
    void destructDataArray(float *** table);

    /// Deleted this->matrix
    void destructMatrix();

    /// Deleted this->colors
    void destructColors();

    /// Deleted this->normalVector
    void destructNormalVector();

public:

    /// Deleted all egg matrix from memory
    ~Egg();

    int n;
    /// 0 - draw points
    /// 1 - draw lines
    /// 2 - drwa traingles
    int renderType;

    float posX, posY, posZ;

    void transform2Egg();

    void randColors();
    void fourColors();
    void deleteSeam();

    void insertVertexWithColor(int i, int j);

    void drawPoints();
    void drawLines();
    void drawTriangles();

    void destruct();
    void draw();

};