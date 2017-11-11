
#encoding=utf-8  
  
# List Of English Stop Words  
# http://armandbrahaj.blog.al/2009/04/14/list-of-english-stop-words/  
_WORD_MIN_LENGTH = 3  
_STOP_WORDS = frozenset([  
'a', 'about', 'above', 'above', 'across', 'after', 'afterwards', 'again',   
'against', 'all', 'almost', 'alone', 'along', 'already', 'also','although',  
'always','am','among', 'amongst', 'amoungst', 'amount',  'an', 'and', 'another',  
'any','anyhow','anyone','anything','anyway', 'anywhere', 'are', 'around', 'as',  
'at', 'back','be','became', 'because','become','becomes', 'becoming', 'been',   
'before', 'beforehand', 'behind', 'being', 'below', 'beside', 'besides',   
'between', 'beyond', 'bill', 'both', 'bottom','but', 'by', 'call', 'can',   
'cannot', 'cant', 'co', 'con', 'could', 'couldnt', 'cry', 'de', 'describe',   
'detail', 'do', 'done', 'down', 'due', 'during', 'each', 'eg', 'eight',   
'either', 'eleven','else', 'elsewhere', 'empty', 'enough', 'etc', 'even',   
'ever', 'every', 'everyone', 'everything', 'everywhere', 'except', 'few',   
'fifteen', 'fify', 'fill', 'find', 'fire', 'first', 'five', 'for', 'former',   
'formerly', 'forty', 'found', 'four', 'from', 'front', 'full', 'further', 'get',  
'give', 'go', 'had', 'has', 'hasnt', 'have', 'he', 'hence', 'her', 'here',   
'hereafter', 'hereby', 'herein', 'hereupon', 'hers', 'herself', 'him',   
'himself', 'his', 'how', 'however', 'hundred', 'ie', 'if', 'in', 'inc',   
'indeed', 'interest', 'into', 'is', 'it', 'its', 'itself', 'keep', 'last',   
'latter', 'latterly', 'least', 'less', 'ltd', 'made', 'many', 'may', 'me',   
'meanwhile', 'might', 'mill', 'mine', 'more', 'moreover', 'most', 'mostly',   
'move', 'much', 'must', 'my', 'myself', 'name', 'namely', 'neither', 'never',   
'nevertheless', 'next', 'nine', 'no', 'nobody', 'none', 'noone', 'nor', 'not',   
'nothing', 'now', 'nowhere', 'of', 'off', 'often', 'on', 'once', 'one', 'only',  
'onto', 'or', 'other', 'others', 'otherwise', 'our', 'ours', 'ourselves', 'out',  
'over', 'own','part', 'per', 'perhaps', 'please', 'put', 'rather', 're', 'same',  
'see', 'seem', 'seemed', 'seeming', 'seems', 'serious', 'several', 'she',   
'should', 'show', 'side', 'since', 'sincere', 'six', 'sixty', 'so', 'some',   
'somehow', 'someone', 'something', 'sometime', 'sometimes', 'somewhere',   
'still', 'such', 'system', 'take', 'ten', 'than', 'that', 'the', 'their',   
'them', 'themselves', 'then', 'thence', 'there', 'thereafter', 'thereby',   
'therefore', 'therein', 'thereupon', 'these', 'they', 'thickv', 'thin', 'third',  
'this', 'those', 'though', 'three', 'through', 'throughout', 'thru', 'thus',   
'to', 'together', 'too', 'top', 'toward', 'towards', 'twelve', 'twenty', 'two',   
'un', 'under', 'until', 'up', 'upon', 'us', 'very', 'via', 'was', 'we', 'well',   
'were', 'what', 'whatever', 'when', 'whence', 'whenever', 'where', 'whereafter',  
'whereas', 'whereby', 'wherein', 'whereupon', 'wherever', 'whether', 'which',   
'while', 'whither', 'who', 'whoever', 'whole', 'whom', 'whose', 'why', 'will',   
'with', 'within', 'without', 'would', 'yet', 'you', 'your', 'yours', 'yourself',  
'yourselves', 'the'])  
  
def word_split(text):  
    word_list = []  
    wcurrent = []  
  
    for i, c in enumerate(text):  
        #if c.isalnum():
        if c.isalpha():  
            wcurrent.append(c)  
        elif wcurrent:  
            word = u''.join(wcurrent)  
            word_list.append(word)  
            wcurrent = []  
  
    if wcurrent:  
        word = u''.join(wcurrent)  
        word_list.append(word)  
  
    return word_list  
  
def words_cleanup(words):  
    """  
    Remove words with length less then a minimum and stopwords.  
    """  
    cleaned_words = []  
    for word in words:  
        if len(word) < _WORD_MIN_LENGTH or word in _STOP_WORDS:  
            continue  
        cleaned_words.append(word)  
    return cleaned_words  
  
def words_normalize(words):  
    """  
    Do a normalization precess on words. In this case is just a tolower(),  
    but you can add accents stripping, convert to singular and so on...  
    """  
    normalized_words = []  
    for word in words:  
        wnormalized = word.lower()  
        normalized_words.append( wnormalized)  
    return normalized_words  
  
def text2array(text):  
    """  
    Just a helper method to process a text.  
    It calls word split, normalize and cleanup.  
    """  
    words = word_split(text)  
    words = words_normalize(words)  
    words = words_cleanup(words)  
    return words  
  

  
 
  

  
if __name__ == '__main__':  
	print