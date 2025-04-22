#include <windows.h>
#include <cmath>
#include "GL/glut.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Product {
    int id;
    string name;
    float price;
    int quantity;
};

vector<Product> stock;

int screenWidth, screenHeight;

float maxQuantity() {
    if (stock.empty()) {
        return 1.0f;
    }

    float maxVal = stock[0].quantity;
    for (unsigned int i = 1; i < stock.size(); i++) {
        if (stock[i].quantity > maxVal) {
            maxVal = stock[i].quantity;
        }
    }
    return maxVal;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float maxVal = maxQuantity();
    float barWidth = static_cast<float>(screenWidth) / stock.size();

    // For title "Stock"
    glColor3f(1.0f, 1.0f, 1.0f); 
    glRasterPos2f((screenWidth - 50) / 2.0 - 25, screenHeight - 20); 
    for (char c : "Stock") {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    for (unsigned int i = 0; i < stock.size(); i++) {
        // For Product Title
        glColor3f(1.0f, 1.0f, 1.0f); 
        glRasterPos2f(i * barWidth + 5, stock[i].quantity / maxVal * (screenHeight - 60) + 20); 
        for (char c : stock[i].name) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
        }

        // For Color of Bar by Threashold quantity 
        if (stock[i].quantity < 100) {
            glColor3f(1.0f, 0.0f, 0.0f);
        } else {
            glColor3f(1.0f, 1.0f, 1.0f);
        }

        glBegin(GL_QUADS);
        glVertex2f(i * barWidth + 5, 0);                                
        glVertex2f((i + 1) * barWidth - 5, 0);                          
        glVertex2f((i + 1) * barWidth - 5, stock[i].quantity / maxVal * (screenHeight - 50)); 
        glVertex2f(i * barWidth + 5, stock[i].quantity / maxVal * (screenHeight - 50));     
        glEnd();

        // For Product Quantity
        glColor3f(0.0f, 0.0f, 0.0f); 
        glRasterPos2f(i * barWidth + barWidth / 2 - 5, 5); 
        for (char c : to_string(stock[i].quantity)) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
        }
    }

    glFlush();
}


void init() {
    screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Stock Quantity Graph");

    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);

    ifstream file("stock.txt");
    if (!file) {
        cout << "Error opening file for reading stock data!\n";
        return;
    }

    stock.clear();

    Product product;
    while (file >> product.id >> product.name >> product.price >> product.quantity) {
        stock.push_back(product);
    }

    file.close();

    glutDisplayFunc(display);
    glutMainLoop();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    init();
    return 0;
}



// void display() {
//     glClear(GL_COLOR_BUFFER_BIT);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();

//     float maxVal = maxQuantity();
//     float barWidth = static_cast<float>(screenWidth) / stock.size();

//     // For title "Stock"
//     glColor3f(1.0f, 1.0f, 1.0f); 
//     glRasterPos2f((screenWidth - 50) / 2.0 - 25, screenHeight - 20); 
//     for (char c : "Stock") {
//         glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
//     }

//     for (unsigned int i = 0; i < stock.size(); i++) {
//         // For Product Title
//         glColor3f(1.0f, 1.0f, 1.0f); 
//         glRasterPos2f(i * barWidth + 5, stock[i].quantity / maxVal * (screenHeight - 60) + 20); 
//         for (char c : stock[i].name) {
//             glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
//         }

//         glBegin(GL_QUADS);
//         glVertex2f(i * barWidth + 5, 0);                                
//         glVertex2f((i + 1) * barWidth - 5, 0);                          
//         glVertex2f((i + 1) * barWidth - 5, stock[i].quantity / maxVal * (screenHeight - 50)); 
//         glVertex2f(i * barWidth + 5, stock[i].quantity / maxVal * (screenHeight - 50));     
//         glEnd();

//         // For Product Quantity
//         glColor3f(0.0f, 0.0f, 0.0f); 
//         glRasterPos2f(i * barWidth + barWidth / 2 - 5, 5); 
//         for (char c : to_string(stock[i].quantity)) {
//             glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
//         }
//     }

//     glFlush();
// }