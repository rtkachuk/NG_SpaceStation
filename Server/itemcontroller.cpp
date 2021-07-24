#include "itemcontroller.h"

ItemController::ItemController()
{

}

QByteArray ItemController::getItem(position cords)
{
    if(ids.contains(cords))
        return ids[cords];
    else
        return "";
}
