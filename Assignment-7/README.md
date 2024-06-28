Search Results Ranking and Querying LLM (Sept, 2023 - Nov, 2023) Developed an advanced algorithm to identify top-k relevant paragraphs from large corpuses, including "The Collected Works of Mahatma Gandhi" and selected works of Maharishi Ramana. 
Corpus Insertion: In the QNA_tool class, we created a vector (corpus) to store paragraphs. 
Initially, the entire corpus was inserted by passing four parameters: book_code, page, para, and sentence_no. 
During this process, the frequency of words was also updated. 
Top-K Paragraph Ranking: Preprocessed the question by converting it to lowercase. Stored the frequency of words in the question in a vector (vector<Duo>res). 
Checked if each word in the preprocessed question was present in the corpus, using the previously stored word frequencies. 
Calculated the score of each paragraph using the formula: ∑ 𝑓 ( 𝑤 ) ⋅ 𝑠 ( 𝑤 ) ∑f(w)⋅s(w) over all words in the paragraph, where 𝑓 ( 𝑤 ) f(w) is the frequency of the word in the paragraph, and 𝑠 ( 𝑤 ) s(w) is the specific corpus frequency + 1 divided by the general corpus frequency + 1 (from unigram.csv). 
Porter Stemmer Integration: Implemented the Porter Stemmer to handle grammatical variations (e.g., treating "bringing" and "brings" as the same word). 
During corpus insertion, each word in the sentence was stemmed before being pushed into the corpus. For top-k paragraph ranking, the only change in the scoring function was to prioritize simultaneous presence of query words by using the formula: Score_para += (internal_word.query_freq * 1000 + freq_word), ensuring higher weight for concurrent query word presence.


In Prolog, "choice points" are used to manage the decision-making process during backtracking. When the Prolog interpreter encounters a situation where multiple rules or solutions are possible, it creates a choice point to keep track of the alternative paths it can take if the current path fails.
