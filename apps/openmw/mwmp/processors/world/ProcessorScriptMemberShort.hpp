#ifndef OPENMW_PROCESSORSCRIPTMEMBERSHORT_HPP
#define OPENMW_PROCESSORSCRIPTMEMBERSHORT_HPP

#include "../WorldProcessor.hpp"

namespace mwmp
{
    class ProcessorScriptMemberShort : public WorldProcessor
    {
    public:
        ProcessorScriptMemberShort()
        {
            BPP_INIT(ID_SCRIPT_MEMBER_SHORT)
        }

        virtual void Do(ObjectPacket &packet, ObjectList &objectList)
        {
            LOG_MESSAGE_SIMPLE(Log::LOG_VERBOSE, "Received %s", strPacketID.c_str());
            objectList.setMemberShorts();
        }
    };
}

#endif //OPENMW_PROCESSORSCRIPTMEMBERSHORT_HPP
