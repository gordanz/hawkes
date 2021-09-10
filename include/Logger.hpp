#ifndef __LOGGER_H__
#define __LOGGER_H__

class Logger
{
public:
    int level;

public:
    Logger(int level) : level(level) {};
};

#endif // __LOGGER_H__