#include <iostream>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

// Function to simulate FIFO page replacement algorithm
int FIFO(char pages[], int num_pages, int num_frames, int& page_replacements) {
    int page_faults = 0;
    page_replacements = 0;
    queue<char> frame_queue;
    bool in_frames[26] = {false}; // Assuming page reference string consists of characters from 'a' to 'z'

    for (int i = 0; i < num_pages; ++i) {
        char page = pages[i] - 'a'; // Convert character to index (0-25)
        if (!in_frames[page]) {
            page_faults++;
            if (frame_queue.size() == num_frames) {
                char replaced_page = frame_queue.front();
                frame_queue.pop();
                in_frames[replaced_page] = false;
                page_replacements++;
            }
            frame_queue.push(page);
            in_frames[page] = true;
        }
    }

    return page_faults;
}

// Function to simulate LRU page replacement algorithm
int LRU(char pages[], int num_pages, int num_frames, int& page_replacements) {
    int page_faults = 0;
    page_replacements = 0;
    int frame_index = 0;
    char frames[num_frames];
    int last_used[26] = {0}; // Array to store last used index for each page (0-25)

    for (int i = 0; i < num_pages; ++i) {
        char page = pages[i] - 'a'; // Convert character to index (0-25)
        bool found = false;
        for (int j = 0; j < frame_index; ++j) {
            if (frames[j] == page) {
                found = true;
                last_used[page] = i;
                break;
            }
        }
        if (!found) {
            page_faults++;
            if (frame_index == num_frames) {
                int replace_page = 0;
                for (int j = 1; j < num_frames; ++j) {
                    if (last_used[frames[j]] < last_used[frames[replace_page]]) {
                        replace_page = j;
                    }
                }
                frames[replace_page] = page;
                last_used[page] = i;
                page_replacements++;
            } else {
                frames[frame_index++] = page;
                last_used[page] = i;
            }
        }
    }

    return page_faults;
}

// Function to simulate OPTIMAL page replacement algorithm
// Function to simulate OPTIMAL page replacement algorithm
int OPTIMAL(char pages[], int num_pages, int num_frames, int& page_replacements) {
    int page_faults = 0;
    page_replacements = 0;
    char frames[num_frames];
    int faults = 0;
    int replacements = 0;

    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < num_pages; i++) {
        bool found = false;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == pages[i]) {
                found = true;
                break;
            }
        }
        if (!found) {
            int index = -1;
            int farthest = i + 1;
            for (int j = 0; j < num_frames; j++) {
                int k;
                for (k = i + 1; k < num_pages; k++) {
                    if (frames[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            index = j;
                        }
                        break;
                    }
                }
                if (k == num_pages) {
                    index = j;
                    break;
                }
            }
            if (frames[index] != -1) {
                replacements++;
            }
            frames[index] = pages[i];
            faults++;
        }
    }

    page_faults = faults;
    page_replacements = replacements;
    return page_faults;
}

// Function to simulate LFU page replacement algorithm
// Function to simulate LFU page replacement algorithm
int LFU(char pages[], int num_pages, int num_frames, int& page_replacements) {
    int page_faults = 0;
    page_replacements = 0;
    int frame[num_frames];
    int freq[num_frames];
    for (int i = 0; i < num_frames; i++) {
        frame[i] = -1;
        freq[i] = 0;
    }

    for (int i = 0; i < num_pages; i++) {
        bool found = false;
        for (int j = 0; j < num_frames; j++) {
            if (frame[j] == pages[i]) {
                freq[j]++;
                found = true;
                break;
            }
        }
        if (!found) {
            int lfu_index = 0;
            int min_freq = INT_MAX;
            for (int j = 0; j < num_frames; j++) {
                if (freq[j] < min_freq) {
                    min_freq = freq[j];
                    lfu_index = j;
                }
            }
            if (frame[lfu_index] != -1) {
                page_replacements++;
            }
            frame[lfu_index] = pages[i];
            freq[lfu_index] = 1;
            page_faults++;
        }
    }

    return page_faults;
}


int main() {
    int num_pages, num_frames;
    cout << "Enter the number of pages: ";
    cin >> num_pages;
    char pages[num_pages];
    cout << "Enter the page reference string (characters a-z, separated by spaces): ";
    for (int i = 0; i < num_pages; ++i) {
        cin >> pages[i];
    }
    cout << "Enter the number of free frames: ";
    cin >> num_frames;
    cout<<"\nName : Nitya Maheshwari\n";
    cout<<"Results\n";
    int page_replacements = 0;
    cout << "-----------------------------------------------------------------------" << endl;
    cout<< "Algorithm\t\t\t" << "Page Faults\t\t\t" <<"Page Replacements\t\t\t" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    int fifo_faults = FIFO(pages, num_pages, num_frames, page_replacements);
    cout << "FIFO:\t\t\t" << fifo_faults << " page faults\t\t\t" << page_replacements << " page replacements\n";

    int lru_faults = LRU(pages, num_pages, num_frames, page_replacements);
    cout << "LRU:\t\t\t" << lru_faults << " page faults\t\t\t" << page_replacements << " page replacements\n";

    int lfu_faults = LFU(pages, num_pages, num_frames, page_replacements);
    cout << "LFU:\t\t\t" << lfu_faults << " page faults\t\t\t" << page_replacements << " page replacements\n";
    
    int optimal_faults = OPTIMAL(pages, num_pages, num_frames, page_replacements);
    cout << "OPTIMAL:\t\t" << optimal_faults << " page faults\t\t\t" << page_replacements << " page replacements\n";
    cout << "-----------------------------------------------------------------------" << endl;
    cout<<"\nEnrollment no.: 0827CS221185\n";
    
     string most_efficient;
    int min_faults = min({fifo_faults, lru_faults, lfu_faults, optimal_faults});
    if (min_faults == fifo_faults) {
        most_efficient = "FIFO";
    } else if (min_faults == lru_faults) {
        most_efficient = "LRU";
    } else if (min_faults == lfu_faults) {
        most_efficient = "LFU";
    } else {
        most_efficient = "OPTIMAL";
    }

    cout << "\nMost Efficient Algorithm: " << most_efficient << endl;
    return 0;
}