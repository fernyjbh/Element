
#pragma once

#include "controllers/Controller.h"
#include "engine/AudioEngine.h"
#include "engine/GraphProcessor.h"

namespace Element {

class FilterInGraph;
class GraphController;
class PluginManager;

class GraphController : public ChangeBroadcaster,
                        public Controller
{
public:
    static const uint32 invalidNodeId   = KV_INVALID_PORT;
    static const int invalidChannel     = -1;
    typedef GraphNodePtr NodePtr;

    GraphController (GraphProcessor&, PluginManager&);
    ~GraphController();

    GraphProcessor& getGraph() noexcept { return processor; }

    PluginManager& plugins() { return pluginManager; }

    int getNumFilters() const noexcept;

    const NodePtr getNode (const int index) const noexcept;
    const NodePtr getNodeForId (const uint32 uid) const noexcept;

    uint32 addFilter (const PluginDescription* desc, double x = 0.0f, double y = 0.0f,
                      uint32 nodeId = 0);

    void removeFilter (const uint32 filterUID);
    void disconnectFilter (const uint32 filterUID);


    int getNumConnections() const noexcept;
    const GraphProcessor::Connection* getConnection (const int index) const noexcept;

    const GraphProcessor::Connection*
    getConnectionBetween (uint32 sourceNode, int sourcePort,
                          uint32 destNode, int destPort) const noexcept;

    bool canConnect (uint32 sourceFilterUID, int sourceFilterChannel,
                     uint32 destFilterUID, int destFilterChannel) const noexcept;

    bool addConnection (uint32 sourceFilterUID, int sourceFilterChannel,
                        uint32 destFilterUID, int destFilterChannel);

    void removeConnection (const int index);

    void removeConnection (uint32 sourceNode, uint32 sourcePort,
                           uint32 destNode, uint32 destPort);

    void removeIllegalConnections();

    void clear();

    /** The special channel index used to refer to a filter's midi channel. */
    static const int midiChannelNumber;

private:
    PluginManager& pluginManager;
    GraphProcessor& processor;

    uint32 lastUID;
    uint32 getNextUID() noexcept;
    inline void changed() { sendChangeMessage(); }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphController)
};
    
class RootGraphController : public GraphController {
public:
    RootGraphController (RootGraph& graph, PluginManager& plugins)
        : GraphController (graph, plugins),
          root (graph)
    { }
    ~RootGraphController() { }
    
    RootGraph& getRootGraph() const { return root; }
private:
    RootGraph& root;
};

}
