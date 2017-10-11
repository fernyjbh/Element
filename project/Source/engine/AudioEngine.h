/*
    AudioEngine.h - This file is part of Element
    Copyright (C) 2016 Kushview, LLC.  All rights reserved.
*/

#pragma once

#include "ElementApp.h"
#include "engine/Engine.h"
#include "engine/GraphProcessor.h"
#include "session/DeviceManager.h"
namespace Element {

class Globals;
class ClipFactory;
class EngineControl;
class GraphProcessor;
class PatternInterface;
class Pattern;
class Transport;
    
class RootGraph : public GraphProcessor
{
public:
    RootGraph() { }
    ~RootGraph() { }
    
    void setPlayConfigFor (AudioIODevice* device);
    void setPlayConfigFor (const DeviceManager::AudioDeviceSetup& setup);
};

class AudioEngine : public Engine
{
public:
    AudioEngine (Globals&);
    ~AudioEngine();

    void activate();
    void deactivate();

    ValueTree createGraphTree();
    void restoreFromGraphTree (const ValueTree&);
    
    // Member access
    Globals& globals();
    RootGraph& getRootGraph();
    Transport* transport();

    // Engine methods
    AudioIODeviceCallback& getAudioIODeviceCallback() override;
    MidiInputCallback& getMidiInputCallback() override;
    
private:
    class Private;
    ScopedPointer<Private> priv;
    Globals& world;
};

typedef ReferenceCountedObjectPtr<AudioEngine> AudioEnginePtr;

}
