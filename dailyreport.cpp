#include "dailyreport.h"

dailyReport::dailyReport()
{
    /*
     * for purchase, from head to tail{
     *      if (is this day){
     *          add this member to dailyMember
     *          add item to daily item()
     *          total revenue+=
     *          if(member is preferred)
     *              preferredMembers++
     *          else if(member is basic)
     *              basicMembers++
     *      }
     * }
     *
     */
}
dailyReport::dailyReport(purchaseHistory allpurchase,string date)
{
    //
    //List<member> dailyMembers;
    //List<Item> dailyInventory;
    /*
     * for purchase, from head to tail{
     *      if (is this day){
     *          add this member to dailyMember
     *          add item to daily item()
     *          total revenue+=
     *          if(member is preferred)
     *              preferredMembers++
     *          else if(member is basic)
     *              basicMembers++
     *      }
     * }
     */
    bool searchCompleted = false;
    node<purchase>* aPurchase=NULL;
    int memPos=0;
    int purPos=0;
    int memPosCheck=-1;
    while(!searchCompleted){
        aPurchase=allpurchase.searchByDate(date,memPos,purPos,searchCompleted);
        if(aPurchase){
            dailyInventory.addToInventory(aPurchase->item.item);
            //if the member pos changed, grab the member ID
            if(memPos!=memPosCheck){
                dailyMembersID.Insert(allpurchase.getID(memPos));
                memPosCheck=memPos;
            }
        }
    }
    totalRevenue = dailyInventory.getTotalValue();
}

string dailyReport::getReport() const{
    string report;
    /*
     * for(dailyMembers, from head to tail){
     *      report = report + name + " " + "preferred/basic" + "; "
     * }
     *
     *  string += "\n"
     *  for(ItemList, from head to tail){
     *      report = report + itemName + quantity + "\n"
     *  }
     */
    node<string>* IDWalker;
    IDWalker = dailyMembersID.begin();
    while(IDWalker){
        report = report + IDWalker->item + " ";
        IDWalker = IDWalker->next;
    }
    return report;
}

int dailyReport::getTotalRevenue() const{
    return totalRevenue;
}

int dailyReport::getPreferredMembers() const{
    return preferredMembers;
}

int dailyReport::getBasicMembers() const{
    return basicMembers;
}
