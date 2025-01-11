#ifndef MEMENTO_HPP
#define MEMENTO_HPP

#include "data_structures/data_buffer.hpp"

class Memento {
public:
    // On utilise DataBuffer comme Snapshot
    using Snapshot = DataBuffer;

    virtual ~Memento() = default;

    // Méthodes publiques pour sauver/charger l'état
    Snapshot save() const {
        Snapshot snapshot;
        _saveToSnapshot(snapshot);
        return snapshot;
    }

    void load(const Snapshot& snapshot) {
        Snapshot mutableSnapshot = snapshot; // Copie pour permettre la lecture
        _loadFromSnapshot(mutableSnapshot);
    }

protected:
    // Méthodes virtuelles protégées pour la sauvegarde/chargement
    virtual void _saveToSnapshot(Snapshot& snapshotToFill) const = 0;
    virtual void _loadFromSnapshot(Snapshot& snapshot) = 0;
};

#endif