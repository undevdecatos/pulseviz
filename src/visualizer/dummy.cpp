#include <GL/glew.h>
#include "dummy.h"

const std::string DummyVisualizerNew::name = "dummy";
const std::string DummyVisualizerNew::title = "Dummy Visualizer";

const std::string& DummyVisualizerNew::getName() const
{
    return this->name;
}

const std::string& DummyVisualizerNew::getTitle() const
{
    return this->title;
}

void DummyVisualizerNew::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0, -1.0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(1.0, -1.0);
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex2f(0.5, 1.0);
    glEnd();
}