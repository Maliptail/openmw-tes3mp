#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/Log.hpp>
#include "PacketContainer.hpp"

using namespace mwmp;

PacketContainer::PacketContainer(RakNet::RakPeerInterface *peer) : ObjectPacket(peer)
{
    packetID = ID_CONTAINER;
    hasCellData = true;
}

void PacketContainer::Packet(RakNet::BitStream *bs, bool send)
{
    if (!PacketHeader(bs, send))
        return;

    RW(objectList->action, send);
    RW(objectList->containerSubAction, send);

    BaseObject baseObject;
    for (unsigned int i = 0; i < objectList->baseObjectCount; i++)
    {
        if (send)
        {
            baseObject = objectList->baseObjects.at(i);
            baseObject.containerItemCount = (unsigned int) (baseObject.containerItems.size());
        }
        else
            baseObject.containerItems.clear();

        Object(baseObject, send);

        RW(baseObject.containerItemCount, send);

        if (baseObject.containerItemCount > maxObjects || baseObject.refId.empty() || (baseObject.refNumIndex != 0 && baseObject.mpNum != 0))
        {
            objectList->isValid = false;
            return;
        }

        ContainerItem containerItem;

        for (unsigned int j = 0; j < baseObject.containerItemCount; j++)
        {
            if (send)
                containerItem = baseObject.containerItems.at(j);

            RW(containerItem.refId, send);
            RW(containerItem.count, send);
            RW(containerItem.charge, send);
            RW(containerItem.enchantmentCharge, send);
            RW(containerItem.actionCount, send);

            if (!send)
                baseObject.containerItems.push_back(containerItem);
        }
        if (!send)
            objectList->baseObjects.push_back(baseObject);
    }
}
