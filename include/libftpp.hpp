#ifndef LIBFTPP_HPP
#define LIBFTPP_HPP

// Data Structures
#include "data_structures/pool.hpp"
#include "data_structures/data_buffer.hpp"

// Design Patterns
#include "design_patterns/memento.hpp"
#include "design_patterns/observer.hpp"
#include "design_patterns/singleton.hpp"
#include "design_patterns/state_machine.hpp"

// Threading
#include "threading/thread_safe_iostream.hpp"
#include "threading/thread_safe_queue.hpp"
#include "threading/thread.hpp"
#include "threading/worker_pool.hpp"
#include "threading/persistant_worker.hpp"

// Network
#include "network/message.hpp"
#include "network/client.hpp"
#include "network/server.hpp"

// Mathematics
#include "mathematics/ivector2.hpp"
#include "mathematics/ivector3.hpp"
#include "mathematics/random_2d_coordinate_generator.hpp"
#include "mathematics/perlin_noise_2d.hpp"

// Bonus
#include "bonus/timer.hpp"
#include "bonus/widget.hpp"
#include "bonus/application.hpp"
#include "bonus/chronometer.hpp"
#include "bonus/observable_value.hpp"
#include "bonus/logger.hpp"

#endif