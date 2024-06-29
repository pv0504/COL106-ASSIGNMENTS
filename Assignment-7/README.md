# Search Results Ranking and Querying LLM (Sept, 2023 - Nov, 2023)

## Overview

Developed an advanced algorithm to identify top-k relevant paragraphs from large corpuses, including "The Collected Works of Mahatma Gandhi" and selected works of Maharishi Ramana.

## Key Features

### Corpus Insertion
- **Vector Storage**: Created a vector (corpus) to store paragraphs.
- **Parameter Passing**: Inserted the entire corpus by passing four parameters: `book_code`, `page`, `para`, and `sentence_no`.
- **Frequency Update**: Updated the frequency of words during the corpus insertion process.

### Top-K Paragraph Ranking
- **Preprocessing**: Converted questions to lowercase.
- **Word Frequency Vector**: Stored the frequency of words in the question in a vector (`vectorres`).
- **Presence Check**: Verified if each word in the preprocessed question was present in the corpus using previously stored word frequencies.
- **Scoring Formula**: Calculated the score of each paragraph using the formula:
  \[
  \text{Score} = \sum f(w) \cdot s(w)
  \]
  where \( f(w) \) is the frequency of the word in the paragraph, and \( s(w) \) is the specific corpus frequency + 1 divided by the general corpus frequency + 1 (from `unigram.csv`).

### Porter Stemmer Integration
- **Grammatical Variations**: Implemented the Porter Stemmer to handle grammatical variations (e.g., treating "bringing" and "brings" as the same word).
- **Corpus Insertion**: Stemmed each word in the sentence before pushing it into the corpus.
- **Scoring Adjustment**: Modified the scoring function to prioritize the simultaneous presence of query words by using the formula:
  \[
  \text{Score\_para} += (\text{internal\_word.query\_freq} \times 1000 + \text{freq\_word})
  \]
  ensuring a higher weight for concurrent query word presence.

# ------------------------------------------------------------
Compilation
To compile the code, use the following command:

g++ tester.cpp dict.cpp search.cpp qna_tool.cpp -o test

This will create an executable file named test.

Execution
To run the program, use the following command:

./test

Output
Upon  execution, you will see the output as the five paragraphs we have returned and the chat GPT’s reply.

Please note that the actual output may vary based on the input data and parameters used.
