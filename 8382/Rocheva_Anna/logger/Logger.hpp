#ifndef LABOOP_LOGGER_HPP
#define LABOOP_LOGGER_HPP


class Logger {
public:
    virtual void setLog(std::string) = 0;
  //  friend std::ostream& operator<<(std::ostream &out, );
private:
    std::string log;
};


#endif //LABOOP_LOGGER_HPP
