#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <map>
#include <functional>
#include <stdexcept>
#include <set>

template<typename TState>
class StateMachine {
public:
    using Action = std::function<void()>;
    
    StateMachine() : m_currentState{} {}

    // Ajouter un état possible
    void addState(const TState& state) {
        m_states.insert(state);
        
        // Ajouter une action vide par défaut
        m_actions[state] = [](){};
    }

    // Ajouter une action pour un état
    void addAction(const TState& state, const Action& lambda) {
        if (m_states.find(state) == m_states.end()) {
            throw std::invalid_argument("State not found");
        }
        m_actions[state] = lambda;
    }

    // Ajouter une transition entre deux états
    void addTransition(const TState& startState, const TState& finalState, const Action& lambda) {
        if (m_states.find(startState) == m_states.end() || m_states.find(finalState) == m_states.end()) {
            throw std::invalid_argument("State not found");
        }
        m_transitions[{startState, finalState}] = lambda;
    }

    // Transitionner vers un nouvel état
    void transitionTo(const TState& state) {
        if (m_states.find(state) == m_states.end()) {
            throw std::invalid_argument("State not found");
        }

        // Si c'est le premier état
        if (m_states.find(m_currentState) == m_states.end()) {
            m_currentState = state;
            return;
        }

        // Chercher la transition
        auto transitionKey = std::make_pair(m_currentState, state);
        auto transitionIt = m_transitions.find(transitionKey);
        
        if (transitionIt == m_transitions.end()) {
            throw std::invalid_argument("Transition not found");
        }

        // Exécuter la transition
        transitionIt->second();
        m_currentState = state;
    }

    // Exécuter l'action de l'état courant
    void update() {
        if (m_states.find(m_currentState) == m_states.end()) {
            throw std::invalid_argument("Current state not found");
        }
        m_actions[m_currentState]();
    }

private:
    std::set<TState> m_states;
    std::map<TState, Action> m_actions;
    std::map<std::pair<TState, TState>, Action> m_transitions;
    TState m_currentState;
};

#endif