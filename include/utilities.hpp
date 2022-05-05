#include <cstdio>
#include <string>

/**
 * @brief Start timer
 * 
 */
void tic(void);
/**
 * @brief Return time after `tic`
 * 
 * @return std::string 
 */
std::string toc(void);
/**
 * @brief Makeshift progress bar.
 * 
 * @param i current position  
 * @param maxi maximal position
 */
void progress_bar(size_t i, size_t maxi);