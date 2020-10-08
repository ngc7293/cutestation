#ifndef CUTE_TOPIC_TOPIC_MANAGER_HH_
#define CUTE_TOPIC_TOPIC_MANAGER_HH_

#include <functional>
#include <memory>
#include <string>

#include "topic.hh"

class TopicManager {
public:
    TopicManager();
    virtual ~TopicManager();

    /** retrieve
     * Templated shorthand for the generic retrieve(name).
     * 
     * @param name name of the topic to fetch.
     * 
     * @return a shared pointer to a Topic. If a Topic named `name` does exist,
     * but does not match typename `T`, the return pointer is empty (invalid)
     */
    template <typename T>
    std::shared_ptr<Topic> retrieve(const std::string& name) 
    {
        return retrieve(name, typeid(T));
    }

    /** retrieve
     * Find and return a Topic of provided name and type. If no Topic of this
     * name exist, one is created.
     * 
     * @param name name of the topic to fetch.
     * @param type topic type
     * 
     * @return a shared pointer to a Topic. If a Topic named `name` does exist,
     * but does not match typename `T`, the return pointer is empty (invalid)
     */
    std::shared_ptr<Topic> retrieve(const std::string& name, const std::type_info& type);

protected:
    /** create
     * Obtains and returns (put does not store) a new Topic with the provided
     * argument. "Obtaining" can be defined by the subclasses. GlobalTopicMgr
     * will create a new instance, whereas the LocalTopicMgr retrieves one from
     * the GlobalTopicMgr.
     * 
     * @param name Topic's name
     * @param type Topic's type
     * 
     * @return a Topic of name and type provided, or a empty shared_ptr if such
     * a topic could not be created. This could be due to conflict with an
     * existing topic.
     */
    virtual std::shared_ptr<Topic> create(const std::string& name, const std::type_info& type) const = 0;

private:
    /** find
     * Find and return a topic
     * 
     * @param name Topic's name
     * 
     * @return a shared pointer to the Topic, or an empty pointer if none exists
     */
    std::shared_ptr<Topic> find(const std::string& name) const;

    /** put
     * Add a topic to internal store
     * 
     * @param topic shared pointer to the Topic to add
     * 
     * @return the same shared_ptr, or an empty one if an error occured (in 
     * which case the topic was not stored.)
     */
    std::shared_ptr<Topic> put(const std::shared_ptr<Topic>& topic);

private:
    struct Priv;
    std::unique_ptr<Priv> d_;
};

#endif