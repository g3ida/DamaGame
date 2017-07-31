#pragma once

namespace Shapes
{
    void drawCircle(float cx, float cy, float r, int num_segments);
    void drawCircleFilled(float cx, float cy, float r, int num_segments);

    void drawRectangleFilled(float x, float y, float w, float h, bool originAtCenter = true);
    void drawRectangle(float x, float y, float w, float h, bool originAtCenter = true);

    void drawKing(float x, float y, float size);

};
