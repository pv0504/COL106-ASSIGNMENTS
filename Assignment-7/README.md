-- insert the corpus
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


----- but in the second case , we are using porter stemmer for handing the grammatical 
errors (for example :- using porter stemmer code, bringing and brings were similar words.)

-- insert the corpus :-
now on inserting the sentence, stem each word of the sentence, and then push the sentence
in the corpus.

-- and in getting top k paragraph, everything is same, only score function is changed.
Score_para += (internal_word.query_freq * 1000 + freq_wor); 
// since frequency can this weight as max words 
in paragraph is 1140//we give priority simultaneos presence of query word than individual freq;
