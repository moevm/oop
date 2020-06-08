#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>
#include <memory>
#include <string>

namespace sf {
    class Texture;
}

class ResourceManager
{
private:
    std::map<const std::string, sf::Texture*> textures;

public:
    struct unknown_resource:  public std::exception
    {
    private:
        const char *msg;

    public:
        std::string str;
        unknown_resource(const char *msg, const std::string& str):
            msg(msg), str(str) {}
        const char * what() const throw()
        {
            return msg;
        }
    };

    struct wrong_id: public std::exception
    {
    private:
        const char *msg;

    public:
        std::string str;
        wrong_id(const char *msg, const std::string& str):
            msg(msg), str(str){}
        const char * what() const throw()
        {
            return msg;
        }
    };

    ResourceManager(const ResourceManager&) =  delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(){}
    ~ResourceManager();

    void loadTexture(const std::string &id,
                     const std::string &path,
                     bool smooth = 0);
    const sf::Texture& getTexture(const std::string &id) const;
};

#endif // RESOURCEMANAGER_H
