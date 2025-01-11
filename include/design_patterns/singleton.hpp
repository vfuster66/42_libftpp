#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <stdexcept>
#include <memory>

template<typename TType>
class Singleton {
public:

    // Empêcher la copie et l'assignation
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Récupérer l'instance
    static TType* instance() {
        if (!m_instance) {
            throw std::runtime_error("Instance not yet created");
        }
        return m_instance.get();
    }

    // Créer l'instance avec des arguments variables
    template<typename... TArgs>
    static void instantiate(TArgs&&... p_args) {
        if (m_instance) {
            throw std::runtime_error("Instance already created");
        }
        m_instance = std::unique_ptr<TType>(new TType(std::forward<TArgs>(p_args)...));
    }

private:
    // Constructeur privé
    Singleton() = default;
    
    // L'instance unique
    static std::unique_ptr<TType> m_instance;
};

// Initialisation du membre statique
template<typename TType>
std::unique_ptr<TType> Singleton<TType>::m_instance;

#endif