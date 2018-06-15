#include "RoomViewModel.h"

RoomViewModel RoomViewModel::createRoomViewModel(int roomType, bool visited, int barrierType)
{
    RoomViewModel room1;
    room1.init(roomType, visited，barrierType);
    return room1;
}

void RoomViewModel::init(int roomType, bool visited, int barrierType)
{
    this->visited = visited;
    this->room_type = roomType;

    for (int i = 0; i < GRID_WIDTH; i++)
        for (int j = 0; j < GRID_HEIGHT; j++)
            room_map[i][j] = 0;

    //生成房间地形,放入石头
    //棋盘中0表示空地，1表示小石头，2表示大石头，3表示玩家
    //4~19表示怪物的各种类别,20~30item
    if (barrierType == 0)
    {
        //没有石头
    }
    else if (barrierType == 1)
    {
        //0,0,0,0,0,0,0,0,0,0,0,0,0
        //0,0,0,0,0,0,0,0,0,0,0,0,0
        //0,0,0,0,0,0,1,0,0,0,0,0,0
        //0,0,1,1,1,1,1,1,1,1,1,0,0
        //0,0,0,0,0,0,1,0,0,0,0,0,0
        //0,0,0,0,0,0,0,0,0,0,0,0,0
        //0,0,0,0,0,0,0,0,0,0,0,0,0
        for (int i = 2; i <= 10; i++)
            room_map[i][GRID_HEIGHT_HALF] = 1;
        for (int i = 2; i <= 4; i++)
            room_map[GRID_WIDTH_HALF][i] = 1;
    }
    else if (barrierType == 2)
    {
        //0,0,0,0,0,0,0,0,0,0,0,0,0
        //0,0,0,2,2,0,0,0,2,2,0,0,0
        //0,0,0,2,2,0,0,0,2,2,0,0,0
        //0,0,0,0,0,0,0,0,0,0,0,0,0
        //0,0,0,2,2,0,0,0,2,2,0,0,0
        //0,0,0,2,2,0,0,0,2,2,0,0,0
        //0,0,0,0,0,0,0,0,0,0,0,0,0
        room_map[3][1] = 2;
        room_map[4][1] = 2;
        room_map[3][2] = 2;
        room_map[4][2] = 2;
        room_map[3][4] = 2;
        room_map[4][4] = 2;
        room_map[3][5] = 2;
        room_map[4][5] = 2;
        room_map[8][1] = 2;
        room_map[9][1] = 2;
        room_map[8][2] = 2;
        room_map[9][2] = 2;
        room_map[8][4] = 2;
        room_map[9][4] = 2;
        room_map[8][5] = 2;
        room_map[9][5] = 2;
    }

    //roomType:0：初始房间
    //roomType:1~7怪物房间
    //1:全Fatty,2:全Fly ,3:全Gaper ,4:全Spider
    //5:Spider+FattyFire,6:Fly+FlyFire,7:Fly+GaperFire
    //roomType:8~14宝藏房间
    //roomType:15~20代表Boss房
    //15~17 Boss1
    //18~20 Boss2
    //根据roomType放入怪物
    //怪物标号：4:Fatty, 5:Fly, 6:Gaper, 7:Spider
    //怪物标号：8:FattyFire, 9:FlyFire, 10:GaperFire
    if (!visited)
    {
        if (roomType == 1) //1:全Fatty
        {
            const int Fatty_num = rand() % 4 + 2;
            for (int i = 0; i < Fatty_num; i++)
            {
                int posX = rand() % GRID_WIDTH, posY = rand() % GRID_HEIGHT;
                while (room_map[posX][posY] != 0)
                {
                    posX = rand() % GRID_WIDTH;
                    posY = rand() % GRID_HEIGHT;
                }
                room_map[posX][posY] = 4;
            }
        }
        if (roomType == 2)
        { //2:全Fly
            const int Fly_num = rand() % 4 + 2;
            for (int i = 0; i < Fly_num; i++)
            {
                int posX = rand() % GRID_WIDTH, posY = rand() % GRID_HEIGHT;
                while (room_map[posX][posY] != 0)
                {
                    posX = rand() % GRID_WIDTH;
                    posY = rand() % GRID_HEIGHT;
                }
                room_map[posX][posY] = 5;
            }
        }
        if (roomType == 3)
        { //3:全Gaper
            const int Gaper_num = rand() % 4 + 2;
            for (int i = 0; i < Gaper_num; i++)
            {
                int posX = rand() % GRID_WIDTH, posY = rand() % GRID_HEIGHT;
                while (room_map[posX][posY] != 0)
                {
                    posX = rand() % GRID_WIDTH;
                    posY = rand() % GRID_HEIGHT;
                }
                room_map[posX][posY] = 6;
            }
        }
        if (roomType == 4)
        { //4::全Spider
            const int Spider_num = rand() % 2 + 5;
            for (int i = 0; i < Spider_num; i++)
            {
                int posX = rand() % GRID_WIDTH, posY = rand() % GRID_HEIGHT;
                while (room_map[posX][posY] != 0)
                {
                    posX = rand() % GRID_WIDTH;
                    posY = rand() % GRID_HEIGHT;
                }
                room_map[posX][posY] = 7;
            }
            room_map[6][3] = 8;
        }
        if (roomType == 5) //5:Spider+FattyFire
        {
            const int Spider_num = rand() % 3 + 2;
            for (int i = 0; i < Spider_num; i++)
            {
                int posX = rand() % GRID_WIDTH, posY = rand() % GRID_HEIGHT;
                while (room_map[posX][posY] != 0)
                {
                    posX = rand() % GRID_WIDTH;
                    posY = rand() % GRID_HEIGHT;
                }
                room_map[posX][posY] = 7;
            }
            const int FattyFire_num = rand() % 2 + 1;
            for (int i = 0; i < FattyFire_num; i++)
            {
                int posX = rand() % GRID_WIDTH, posY = rand() % GRID_HEIGHT;
                while (room_map[posX][posY] != 0)
                {
                    posX = rand() % GRID_WIDTH;
                    posY = rand() % GRID_HEIGHT;
                }
                room_map[posX][posY] = 8;
            }
        }
        if (roomType == 6)
        { //6:Fly+FlyFire
            const int Fly_num = rand() % 2 + 3;
            for (int i = 0; i < Fly_num; i++)
            {
                int posX = rand() % GRID_WIDTH, posY = rand() % GRID_HEIGHT;
                while (room_map[posX][posY] != 0)
                {
                    posX = rand() % GRID_WIDTH;
                    posY = rand() % GRID_HEIGHT;
                }
                room_map[posX][posY] = 5;
            }
            const int FlyFire_num = rand() % 2 + 3;
            for (int i = 0; i < FlyFire_num; i++)
            {
                int posX = rand() % GRID_WIDTH, posY = rand() % GRID_HEIGHT;
                while (room_map[posX][posY] != 0)
                {
                    posX = rand() % GRID_WIDTH;
                    posY = rand() % GRID_HEIGHT;
                }
                room_map[posX][posY] = 9;
            }
        }
        if (roomType == 7)
        { //7:Fly+GaperFire
            const int Fly_num = rand() % 2 + 2;
            for (int i = 0; i < Fly_num; i++)
            {
                int posX = rand() % GRID_WIDTH, posY = rand() % GRID_HEIGHT;
                while (room_map[posX][posY] != 0)
                {
                    posX = rand() % GRID_WIDTH;
                    posY = rand() % GRID_HEIGHT;
                }
                room_map[posX][posY] = 5;
            }
            const int GaperFire_num = rand() % 2 + 3;
            for (int i = 0; i < GaperFire_num; i++)
            {
                int posX = rand() % GRID_WIDTH, posY = rand() % GRID_HEIGHT;
                while (room_map[posX][posY] != 0)
                {
                    posX = rand() % GRID_WIDTH;
                    posY = rand() % GRID_HEIGHT;
                }
                room_map[posX][posY] = 10;
            }
        }
    }
}

bool RoomViewModel::is_boss_room() const
{
    return room_type >= 15 && room_type <= 20;
}
