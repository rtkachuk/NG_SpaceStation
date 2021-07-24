#include "itemcontroller.h"

ItemController::ItemController()
{

}

QByteArray ItemController::getItem(position cords)
{
    if(m_ids.contains(cords))
        return m_ids[cords];
    else
        return "";
}
