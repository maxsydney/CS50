import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.tokenizer = nltk.tokenize.TweetTokenizer()
        self.positives = set()
        self.negatives = set()
        with open(positives, 'r') as infile:
            for line in infile:
                if not line.startswith((";", " ")):
                    self.positives.add(line.strip().lower())
        
        with open(negatives, 'r') as infile:
            for line in infile:
                if not line.startswith((";", " ")):
                    self.negatives.add(line.strip().lower())
        

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        score = 0
        tokens = self.tokenizer.tokenize(text)
        for token in tokens:
            if token.lower() in self.positives:
                score += 1
            elif token.lower() in self.negatives:
                score -= 1
        return score

