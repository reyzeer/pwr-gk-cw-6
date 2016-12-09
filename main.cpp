/// Laboratorium: Grafika Komputerowa
/// Prowadzący: Dr inż. Marek Woda
/// Cwiczenie 4
/// Zbigniew Czarnecki 209909

/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacją osi
//  układu współrzednych

/*************************************************************************************/

#include "common.h"

const float MIN_R = 7.0f;
const float MAX_R = 30.0f;
const float SPEED = 0.1f;

typedef float point3[3];
static GLfloat viewer[] = {0.0, 0.0, 10.0};

static GLfloat theta = 0.0;   // kąt obrotu obiektu
static GLfloat phi = 0.0;
static GLfloat r = 10.0;
static GLfloat pix2angle_x;     // przelicznik pikseli na stopnie
static GLfloat pix2angle_y;     // przelicznik pikseli na stopnie

/// stan klawiszy myszy
/// 0 - nie naciśnięto żadnego klawisza
/// 1 - naciśnięty zostać lewy klawisz
static GLint statusKey = 0;

/// poprzednia pozycja kursora myszy
static int x_pos_old = 0;

/// poprzednia pozycja kursora myszy
static int y_pos_old = 0;

/// różnica pomiędzy pozycją bieżącą i poprzednią kursora myszy
static int delta_x = 0;

/// różnica pomiędzy pozycją bieżącą i poprzednią kursora myszy
static int delta_y = 0;

/// false - moving egg
/// true - moving lights
bool moveEggLights = false;

/// Obiekt generujący jajko
Egg egg = Egg();

///Promien sfery swiatel
float lightsR = 10.0;

static GLfloat theta_light[] = {0.0, 0.0};
static GLfloat phi_light[] = {0.0, 0.0};

/// Position of blue light
GLfloat light_position_blue[] = {0.0, 0.0, 10.0, 1.0};

/// Position of red light
GLfloat light_position_red[] = {0.0, 0.0, 10.0, 1.0};

/*************************************************************************************/

/// Funkcja "bada" stan myszy i ustawia wartości odpowiednich zmiennych globalnych
void Mouse(int btn, int state, int x, int y)
{

    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // przypisanie aktualnie odczytanej pozycji kursora
        // jako pozycji poprzedniej
        x_pos_old = x;
        y_pos_old = y;
        statusKey = 1;          // wcięnięty został lewy klawisz myszy
    } else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        x_pos_old = x;
        y_pos_old = y;        // przypisanie aktualnie odczytanej pozycji kursora
        // jako pozycji poprzedniej
        statusKey = 2;            //wciśnięty został prawy klawisz myszy
    } else {
        statusKey = 0;          // nie został wcięnięty żaden klawisz
    }

}

/*************************************************************************************/

/// Funkcja "monitoruje" położenie kursora myszy i ustawia wartości odpowiednich
/// zmiennych globalnych
void Motion( GLsizei x, GLsizei y )
{

    delta_x = x - x_pos_old;     // obliczenie różnicy położenia kursora myszy
    delta_y = y - y_pos_old;     // obliczenie różnicy położenia kursora myszy

    x_pos_old = x;            // podstawienie bieżącego położenia jako poprzednie
    y_pos_old = y;            // podstawienie bieżącego położenia jako poprzednie

    glutPostRedisplay();     // przerysowanie obrazu sceny
}

/*************************************************************************************/

void setTheta()
{
    //jeśli lewy klawisz myszy wciśnięty
    if (statusKey == 1) {
        theta += delta_x * pix2angle_x;    // modyfikacja kąta obrotu o kat proporcjonalny
        if (theta >= 360.0) {
            theta = 0.0;
        }
    }
}

void setPhi()
{
    // jeśli lewy klawisz myszy wcięnięty
    if (statusKey == 1) {
        phi += delta_y * pix2angle_y;    // do różnicy położeń kursora myszy
        if (phi >= 360.0) {
            phi = 0.0;
        }
    }
}

void setR()
{
    if (statusKey == 2) {
        r += 0.1 * delta_y;
        if (r <= MIN_R) { // ograniczenie zblizenia
            r = MIN_R;
        }
        if (r >= MAX_R) { // ograniczenie oddalenia
            r = MAX_R;
        }
    }
}

///Ustawia położenie obserwatora
void setViewer()
{

    if (!moveEggLights) {
        setTheta();
        setPhi();
        setR();
    }

    viewer[0] = r * cos(theta) * cos(phi);
    viewer[1] = r * sin(phi);
    viewer[2] = r * sin(theta) * cos(phi);

    // Zdefiniowanie położenia obserwatora
    gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, cos(phi), 0.0);

}

void prepareEgg()
{

    egg.n = 29;
    egg.posX = 0.0f;
    egg.posY = 5.0f;
    egg.posZ = 0.0f;
    egg.renderType = 2;

}

void setThetaLight(int lightNumber)
{
    theta_light[lightNumber] += delta_x * pix2angle_x;    // modyfikacja kąta obrotu o kat proporcjonalny
    if (theta_light[lightNumber] >= 360.0) {
        theta_light[lightNumber] = 0.0;
    }
}

void setPhiLight(int lightNumber)
{
    phi_light[lightNumber] += delta_y * pix2angle_y;    // do różnicy położeń kursora myszy
    if (phi_light[lightNumber] >= 360.0) {
        phi_light[lightNumber] = 0.0;
    }
}

/// Funkcja określająca co ma być rysowane (zawsze wywoływana gdy trzeba przerysować scenę)
void RenderScene(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Czyszczenie okna aktualnym kolorem czyszczącym

    glLoadIdentity();
    // Czyszczenie macierzy bieżącej


    setViewer();

    RDraw::Axes();
    egg.draw();

    if (moveEggLights) {

        if (statusKey == 1) {
            setThetaLight(0);
            setPhiLight(0);
        } else if (statusKey == 2) {
            setThetaLight(1);
            setPhiLight(1);
        }

    }

    light_position_blue[0] = lightsR * cos(theta_light[0]) * cos(phi_light[0]);
    light_position_blue[1] = lightsR * sin(phi_light[0]);
    light_position_blue[2] = lightsR * sin(theta_light[0]) * cos(phi_light[0]);
    light_position_blue[3] = 1.0;
    glLightfv(GL_LIGHT0, GL_POSITION, light_position_blue);
    //Aktualizacja pozycji swiatla 0

    light_position_red[0] = lightsR * cos(theta_light[1]) * cos(phi_light[1]);
    light_position_red[1] = lightsR * sin(phi_light[1]);
    light_position_red[2] = lightsR * sin(theta_light[1]) * cos(phi_light[1]);
    light_position_red[3] = 1.0;
    glLightfv(GL_LIGHT1, GL_POSITION, light_position_red);
    //Aktualizacja pozycji swiatla 1

    //glutWireTeapot(3.0); // Narysowanie obrazu czajnika do herbaty

    glFlush();
    // Przekazanie poleceń rysujących do wykonania

    glutSwapBuffers();

}

/*************************************************************************************/

void keys(unsigned char key, int x, int y)
{

    switch (key) {

        case 'p':
            //Points
            egg.renderType = 0;
            break;
        case 'w':
            //Lines
            egg.renderType = 1;
            break;
        case 's':
            //Triangles
            egg.renderType = 2;
            break;

        case '[':
            if (egg.n > 1) {
                egg.destruct();
                egg.n -= 2;
            }
            break;
        case ']':
            egg.destruct();
            egg.n += 2;
            break;
        case ',':
            moveEggLights = false;
            break;
        case '.':
            moveEggLights = true;
            break;
    }

    RenderScene(); // przerysowanie obrazu sceny
}

/*************************************************************************************/

void lightBlue()
{
    /*************************************************************************************/
    // Definicja źródła światła

    //GLfloat light_position_blue[] = {0.0, 0.0, 10.0, 1.0};
    // położenie źródła

    GLfloat light_ambient[] = {0.1, 0.1, 0.1, 1.0};
    // składowe intensywności świecenia źródła światła otoczenia
    // Ia = [Iar,Iag,Iab]

    GLfloat light_diffuse[] = {0.0, 0.0, 1.0, 1.0};
    // składowe intensywności świecenia źródła światła powodującego
    // odbicie dyfuzyjne Id = [Idr,Idg,Idb]

    GLfloat light_specular[]= {1.0, 1.0, 1.0, 1.0};
    // składowe intensywności świecenia źródła światła powodującego
    // odbicie kierunkowe Is = [Isr,Isg,Isb]

    GLfloat att_constant  = {1.0};
    // składowa stała ds dla modelu zmian oświetlenia w funkcji
    // odległości od źródła

    GLfloat att_linear    = {0.05};
    // składowa liniowa dl dla modelu zmian oświetlenia w funkcji
    // odległości od źródła

    GLfloat att_quadratic  = {0.001};
    // składowa kwadratowa dq dla modelu zmian oświetlenia w funkcji
    // odległości od źródła

    /*************************************************************************************/
    // Ustawienie parametrów źródła

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position_blue);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

}

void lightRed()
{
    /*************************************************************************************/
    // Definicja źródła światła

    //GLfloat light_position_red[] = {0.0, 0.0, 5.0, 1.0};
    // położenie źródła

    GLfloat light_ambient[] = {0.1, 0.1, 0.1, 1.0};
    // składowe intensywności świecenia źródła światła otoczenia
    // Ia = [Iar,Iag,Iab]

    GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};
    // składowe intensywności świecenia źródła światła powodującego
    // odbicie dyfuzyjne Id = [Idr,Idg,Idb]

    GLfloat light_specular[]= {1.0, 1.0, 1.0, 1.0};
    // składowe intensywności świecenia źródła światła powodującego
    // odbicie kierunkowe Is = [Isr,Isg,Isb]

    GLfloat att_constant  = {1.0};
    // składowa stała ds dla modelu zmian oświetlenia w funkcji
    // odległości od źródła

    GLfloat att_linear    = {0.05};
    // składowa liniowa dl dla modelu zmian oświetlenia w funkcji
    // odległości od źródła

    GLfloat att_quadratic  = {0.001};
    // składowa kwadratowa dq dla modelu zmian oświetlenia w funkcji
    // odległości od źródła

    /*************************************************************************************/
    // Ustawienie parametrów źródła

    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position_red);

    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, att_constant);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, att_linear);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, att_quadratic);

}

/// Funkcja ustalająca stan renderowania
void MyInit(void)
{

    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Kolor czyszcący (wypełnienia okna) ustawiono na czarny

    /*************************************************************************************/
    //  Definicja materiału z jakiego zrobiony jest czajnik
    //  i definicja źródła światła
    /*************************************************************************************/

    /*************************************************************************************/
    // Definicja materiału z jakiego zrobiony jest czajnik

        GLfloat mat_ambient[]  = {1.0, 1.0, 1.0, 1.0};
        // współczynniki ka =[kar,kag,kab] dla światła otoczenia

        GLfloat mat_diffuse[]  = {1.0, 1.0, 1.0, 1.0};
        // współczynniki kd =[kdr,kdg,kdb] światła rozproszonego

        GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
        // współczynniki ks =[ksr,ksg,ksb] dla światła odbitego

        GLfloat mat_shininess  = {20.0};
        // współczynnik n opisujący połysk powierzchni

    /*************************************************************************************/
    // Ustawienie parametrów materiału i źródła światła
    /*************************************************************************************/
    // Ustawienie patrametrów materiału

        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    /*************************************************************************************/
    // Dodanie ustawienie światła

    lightBlue();
    lightRed();

    /*************************************************************************************/
    // Ustawienie opcji systemu oświetlania sceny

        glShadeModel(GL_SMOOTH); // właczenie łagodnego cieniowania
        glEnable(GL_LIGHTING);   // właczenie systemu oświetlenia sceny
        glEnable(GL_LIGHT0);     // włączenie źródła o numerze 0
        glEnable(GL_LIGHT1);     // włączenie źródła o numerze 1
        glEnable(GL_DEPTH_TEST); // włączenie mechanizmu z-bufora

    /*************************************************************************************/

}

/*************************************************************************************/

/// Funkcja ma za zadanie utrzymanie stałych proporcji rysowanych
/// w przypadku zmiany rozmiarów okna.
/// Parametry vertical i horizontal (wysokość i szerokość okna) są
/// przekazywane do funkcji za każdym razem gdy zmieni się rozmiar okna.
void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

    pix2angle_x = 360.0 * SPEED / (float)horizontal;  // przeliczenie pikseli na stopnie
    pix2angle_y = 360.0 * SPEED / (float)vertical;  // przeliczenie pikseli na stopnie

    glMatrixMode(GL_PROJECTION);
    // Przełączenie macierzy bieżącej na macierz projekcji

    glLoadIdentity();
    // Czyszcznie macierzy bieżącej

    //GLdouble aspect = (horizontal > vertical) ? horizontal/vertical : vertical/horizontal;
    GLdouble aspect = (GLdouble) horizontal / (GLdouble) vertical;
    gluPerspective(70.0, aspect, 1.0, 30.0);
    // Ustawienie parametrów dla rzutu perspektywicznego

    glViewport(0, 0, horizontal, vertical);
    // Ustawienie wielkości okna okna widoku (viewport) w zależności
    // relacji pomiędzy wysokością i szerokością okna

    glMatrixMode(GL_MODELVIEW);
    // Przełączenie macierzy bieżącej na macierz widoku modelu

    glLoadIdentity();
    // Czyszczenie macierzy bieżącej

}

/*************************************************************************************/

/// Główny punkt wejścia programu. Program działa w trybie konsoli
int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(450, 450);

    glutCreateWindow("Jajko Cw 5 - Zbigniew Czarnecki 209909");

    glutDisplayFunc(RenderScene);
    // Określenie, że funkcja RenderScene będzie funkcją zwrotną
    // (callback function).  Bedzie ona wywoływana za każdym razem
    // gdy zajdzie potrzba przeryswania okna

    glutReshapeFunc(ChangeSize);
    // Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną
    // zazmiany rozmiaru okna

    glutKeyboardFunc(keys);

    glutMouseFunc(Mouse);
    // Ustala funkcję zwrotną odpowiedzialną za badanie stanu myszy

    glutMotionFunc(Motion);
    // Ustala funkcję zwrotną odpowiedzialną za badanie ruchu myszy

    prepareEgg();

    MyInit();
    // Funkcja MyInit() (zdefiniowana powyżej) wykonuje wszelkie
    // inicjalizacje konieczne  przed przystąpieniem do renderowania

    glEnable(GL_DEPTH_TEST);
    // Włączenie mechanizmu usuwania powierzchni niewidocznych

    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT

    return 0;

}
