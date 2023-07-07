#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H
#include "AllReference.h"
class GraphicsSettings{
    public:
        string title;
        VideoMode resolution;
        bool fullscreen;
        bool verticalSync;
        unsigned frameRateLimit;
        ContextSettings contextSettings;
        vector<VideoMode> videoModes;

        GraphicsSettings();
        void saveToFile( string path);
        void loadFromFile( string path);
};
#endif