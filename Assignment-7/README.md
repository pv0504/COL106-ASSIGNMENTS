get_top_k_para

In QNA_tool class we created vector (corpus) in which it will store paragraphs.
- initally we will insert the complete corpus, by passsing four parameters book_code,page
para,sentence_no,sentence, but here we will store paragraphs.
,at the same time we are updating the frequency of words.

--top k paragraph.

1. first we are preprocessing the question by converting it to small letters.
2. next we are storing the frequency of the words in the question.(in the vector<Duo>res)

3. now we are preprocessing the question, and checking whether the word is present
corpus or not(initally we stored the frequency of all the words in corpus)

and the score calculator of a paragraph is sigma f(w)s(w) over all words in the paragraph
, and the f(w) -> frequency of that word in the paragraph, s(w) = frequency(w) in specific corpus + 1
/frequency(w) in a general corpus + 1, (frequency in general corpus is given in unigram.csv)
