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
        void saveToFile(const string path);
        void loadFromFile(const string path);
};
#endif