#ifndef POOL_HPP
#define POOL_HPP

#include <vector>
#include <queue>
#include <memory>

template<typename TType>
class Pool {
public:

    // Classe imbriquée pour encapsuler les objets acquis
    class Object {
    public:

        // Constructeur prenant un pointeur vers l'objet et une référence vers le pool
        Object(TType* ptr, Pool<TType>& pool) : m_ptr(ptr), m_pool(pool) {}
        
        // Destructeur qui retourne l'objet au pool
        ~Object() {
            if (m_ptr) {
                m_pool.release(m_ptr);
            }
        }

        // Opérateur -> pour accéder aux membres de l'objet
        TType* operator->() { return m_ptr; }
        const TType* operator->() const { return m_ptr; }

        // Empêcher la copie
        Object(const Object&) = delete;
        Object& operator=(const Object&) = delete;

        // Permettre le déplacement
        Object(Object&& other) noexcept : m_ptr(other.m_ptr), m_pool(other.m_pool) {
            other.m_ptr = nullptr;
        }
        
        Object& operator=(Object&& other) noexcept {
            if (this != &other) {
                if (m_ptr) {

                    // Libère l'objet actuel
                    m_pool.release(m_ptr);
                }
                m_ptr = other.m_ptr;

                // Déplace la propriété
                other.m_ptr = nullptr;
            }
            return *this;
        }

    private:

        // Pointeur vers l'objet
        TType* m_ptr;

        // Référence au pool propriétaire
        Pool<TType>& m_pool;
    };

    Pool() = default;
    ~Pool() {
        // Nettoyer tous les objets alloués
        for (auto ptr : m_allocated) {
            delete ptr;
        }
    }

    // Redimensionner le pool avec un nombre spécifique d'objets
    void resize(const size_t& numberOfObjectsStored) {
        while (m_allocated.size() < numberOfObjectsStored) {
            auto* ptr = new TType();
            m_allocated.push_back(ptr);
            m_available.push(ptr);
        }
    }

    // Acquérir un objet du pool avec des arguments optionnels
    template<typename... TArgs>
    Object acquire(TArgs&&... args) {
        TType* ptr;
        if (m_available.empty()) {

            // Si aucun objet n'est disponible, en créer un nouveau
            ptr = new TType(std::forward<TArgs>(args)...);
            m_allocated.push_back(ptr);
        } else {

            // Utiliser un objet existant
            ptr = m_available.front();
            m_available.pop();

            // Reconstruire l'objet avec placement new
            ptr->~TType();
            new (ptr) TType(std::forward<TArgs>(args)...);
        }
        return Object(ptr, *this);
    }

private:

    // Libérer un objet et le remettre dans le pool
    void release(TType* ptr) {
        m_available.push(ptr);
    }

    // Tous les objets alloués
    std::vector<TType*> m_allocated;

    // Objets disponibles pour réutilisation
    std::queue<TType*> m_available;

    // Autorise Object à appeler `release`
    friend class Object;
};

#endif // POOL_HPP