# ARTLibrary-v1.0
A basic library to implement Adaptive Resonance Theory, a special type of Artificial Neural Network designed for unsupervised learning, into your very own Arduino Boards. 
ART (Adaptive Resonance Theory) is a type of artificial neural network (ANN) architecture that was developed by Stephen Grossberg and Gail Carpenter in the 1980s. It is designed to address the stability-plasticity dilemma that is often encountered in neural networks, which refers to the challenge of maintaining stable learning while also adapting to new information.

ART networks are primarily used for unsupervised learning tasks, such as pattern recognition, clustering, and classification. They are particularly effective in situations where the number of categories or patterns is not known in advance and may change dynamically.

The key idea behind ART networks is the concept of resonance, which refers to the matching process between an input pattern and a category in the network. Resonance occurs when the input pattern sufficiently matches a category, leading to the activation and learning of that category. ART networks utilize a vigilance parameter, which determines the level of similarity required for a pattern to activate a category. This parameter allows the network to control its sensitivity to different input patterns.

The ART architecture consists of two main layers: the input layer and the recognition layer. The input layer receives the input patterns, while the recognition layer contains a set of categories that can be activated by the input patterns. Each category has associated weight values that represent its knowledge or prototype.

The ART learning algorithm involves the following steps:

1. Initialization: Initialize the network by setting the vigilance parameter, initializing category weights, and setting the activations of all categories to zero.

2. Recognition: Present an input pattern to the network. The network computes the similarity between the input pattern and each category using a matching equation. The category with the highest similarity, satisfying the vigilance criterion, is selected as the winner.

3. Learning: If the winner meets the vigilance criterion, it indicates a match between the input pattern and an existing category. The weights of the winning category are adjusted to improve the match by updating them based on the input pattern and the previous weight values.

4. Resetting: If the winner does not meet the vigilance criterion, it indicates a mismatch between the input pattern and all existing categories. In such cases, a new category is created by modifying the least activated category or by splitting an existing category.

ART networks exhibit several desirable properties, including stability-plasticity balance, incremental learning, and resistance to noise and interference. They are also capable of adapting to changing environments and can dynamically adjust their category representations as new patterns are encountered.

Overall, ART networks provide a useful framework for addressing pattern recognition and classification tasks, particularly in situations where the number of categories is unknown or may change over time.
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
The ARTLibrary provided above is a simplified implementation of the Adaptive Resonance Theory (ART) architecture for an Arduino board. Let's dive into each component of the library and its functionality:

1. `ARTLibrary` class:
   - The `ARTLibrary` class represents the main implementation of the ART network. It takes the vigilance parameter as a constructor argument, which determines the level of similarity required for a pattern to activate a category.
   - The class includes member variables such as `vigilance`, `weights`, `activations`, `numCategories`, and `numInputs` to store the necessary data for the ART network.

2. `initialize` method:
   - The `initialize` method initializes the ART network by setting the input size (`inputSize`) and category size (`categorySize`).
   - It initializes the weights and activations arrays to zero for all categories.

3. `train` method:
   - The `train` method is responsible for training the ART network with input patterns.
   - It takes an input array of floats (`input[MAX_INPUT_SIZE]`) as the training pattern.
   - The method finds the category with the highest activation based on the input pattern and calculates the activation values for all categories.
   - If the winner category meets the vigilance criterion (similarity >= vigilance), the method updates the weights of the winner category to improve the match with the input pattern.

4. `classify` method:
   - The `classify` method predicts the category for a given input pattern.
   - It takes an input array of floats (`input[MAX_INPUT_SIZE]`) as the input pattern.
   - The method calculates the activation values for all categories based on the input pattern and returns the index of the category with the highest activation.

The library assumes a fixed-size input (`MAX_INPUT_SIZE`) and category (`MAX_CATEGORY_SIZE`) for simplicity. You can modify these constants to fit your specific needs.

To use the library, you need to create an instance of the `ARTLibrary` class, initialize it with the vigilance parameter, and then use the `train` and `classify` methods to train the network and predict categories based on input patterns.

Please note that this implementation is a simplified version of ART and may not include all the intricacies and optimizations found in a full-scale ART implementation.
_____________________________________________________________________________________________________________________________________________________________________
