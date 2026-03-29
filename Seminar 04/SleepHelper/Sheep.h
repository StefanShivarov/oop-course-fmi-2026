#pragma once

class Sheep {
private:
    static int totalSheepCount;
    bool hasJumped = false;
    int id;

public:
    Sheep();
    int getId() const;
    bool jump();
};
