#ifndef __SIMULATE_H__
#define __SIMULATE_H__

std::string simulate_hawkes(int thread_id, uint64_t seed, std::vector<size_t> &N, std::vector<double> &ld, Parameters &p);

#endif // __SIMULATE_H__