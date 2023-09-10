# ART-v1.0
A basic library to implement Adaptive Resonance Theory, a special type of Artificial Neural Network designed for unsupervised learning, into your very own Arduino Boards. 
ART (Adaptive Resonance Theory) is a type of artificial neural network (ANN) architecture that was developed by Stephen Grossberg and Gail Carpenter in the 1980s. It is designed to address the stability-plasticity dilemma that is often encountered in neural networks, which refers to the challenge of maintaining stable learning while also adapting to new information.

ART networks are primarily used for unsupervised learning tasks, such as pattern recognition, clustering, and classification. They are particularly effective in situations where the number of categories or patterns is not known in advance and may change dynamically.

The key idea behind ART networks is the concept of resonance, which refers to the matching process between an input pattern and a category in the network. Resonance occurs when the input pattern sufficiently matches a category, leading to the activation and learning of that category. ART networks utilize a vigilance parameter, which determines the level of similarity required for a pattern to activate a category. This parameter allows the network to control its sensitivity to different input patterns.

The ART architecture consists of two main layers: the input layer and the recognition layer. The input layer receives the input patterns, while the recognition layer contains a set of categories that can be activated by the input patterns. Each category has associated weight values that represent its knowledge or prototype.

The library appears to implement a simplified version of ART1 (Adaptive Resonance Theory 1) neural network architecture. ART1 is one of the fundamental variants of the ART family of neural networks, and it is specifically designed for binary input data, where input features are typically represented as binary values (0 or 1).

ART1 is primarily used for unsupervised learning tasks, such as clustering and pattern recognition, where it dynamically creates and adapts categories to group similar input patterns. The key feature of ART1 is the use of a vigilance parameter, which controls the level of similarity required for input patterns to be assimilated into existing categories.

The library has the following characteristics of ART1:

1. **Binary Input Handling**: ART1 is suitable for binary input data, and your code does not appear to handle continuous-valued input features.

2. **Vigilance Parameter**: Your code includes the `vigilance` parameter, which determines how similar an input pattern must be to an existing category to be assimilated. This is a central aspect of ART1.

3. **Initialization and Training**: Your code includes methods for initializing the network with input data (`initialize`) and training the network (`train`). These are core components of ART1, where categories are created and updated based on input patterns.

While your library implements a simplified version of ART1, it's important to note that there are various extensions and modifications to ART1, such as ART2 and ARTMAP, which handle different types of input data and learning paradigms. These extensions may incorporate real-valued inputs or supervised learning aspects, which the basic ART1 does not cover.

The ART learning algorithm involves the following steps:

1. Initialization: Initialize the network by setting the vigilance parameter, initializing category weights, and setting the activations of all categories to zero.

2. Recognition: Present an input pattern to the network. The network computes the similarity between the input pattern and each category using a matching equation. The category with the highest similarity, satisfying the vigilance criterion, is selected as the winner.

3. Learning: If the winner meets the vigilance criterion, it indicates a match between the input pattern and an existing category. The weights of the winning category are adjusted to improve the match by updating them based on the input pattern and the previous weight values.

4. Resetting: If the winner does not meet the vigilance criterion, it indicates a mismatch between the input pattern and all existing categories. In such cases, a new category is created by modifying the least activated category or by splitting an existing category.

ART networks exhibit several desirable properties, including stability-plasticity balance, incremental learning, and resistance to noise and interference. They are also capable of adapting to changing environments and can dynamically adjust their category representations as new patterns are encountered.

Overall, ART networks provide a useful framework for addressing pattern recognition and classification tasks, particularly in situations where the number of categories is unknown or may change over time.
----------------------------------------------------------------------------------------------------------------------------------------------------------------------

The custom ART (Adaptive Resonance Theory) library I provided allows you to implement a simplified version of an ART-like neural network on an Arduino platform for unsupervised learning and classification tasks. Below, I'll provide a detailed explanation of how to use this custom ART library:

### Step 1: Include the Library
In your Arduino sketch, you first need to include the ART library header file at the beginning of your code:


#include "ART.h"


Step 2: Define Parameters
You should define some essential parameters for your ART network:

- `inputSize`: The dimensionality of your input data. For example, if you're working with 2D data points, set `inputSize` to 2.

- `prototypeSize`: The number of prototype vectors or categories you want your ART network to learn. This determines how many categories the network can classify data into.

- `vigilance`: This parameter controls the network's sensitivity to incoming data. It's a value between 0 and 1. A higher value makes the network less sensitive, while a lower value makes it more sensitive.

Step 3: Create an ART Instance
Create an instance of the ART network with the parameters you defined:


ART art(inputSize, prototypeSize, vigilance);


Step 4: Initialize the Network
In the `setup` function or any initialization routine, you should initialize the ART network with some initial data. This data serves as the starting prototypes or categories that the network will use for comparison when classifying new data. For example:


void setup() {
    // Initialize the ART network with some sample data
    float sample1[inputSize] = {0.1, 0.2};
    float sample2[inputSize] = {0.8, 0.9};
    float sample3[inputSize] = {0.3, 0.4};

    art.initialize(sample1);
    art.initialize(sample2);
    art.initialize(sample3);
}


Here, we've provided three initial data points to the ART network to start with.

Step 5: Classify New Data
In the `loop` function or whenever you want to classify new data, use the `classify` method of the ART instance to determine the category that the new data belongs to:


void loop() {
    // Input data to classify
    float input[inputSize] = {0.6, 0.7};

    // Classify the input data
    int category = art.classify(input);

    // Print the category
    Serial.print("Input belongs to category: ");
    Serial.println(category);

    delay(1000); // Delay for visualization purposes
}


In this example, we provide a new input data point, and the `classify` method returns the category to which the input data is classified.

Important Notes:
- The `initialize` method is used for adding initial data points to the network. These data points serve as the starting prototypes.

- The `train` method is implicitly called within the `classify` method when the input doesn't match any existing category prototypes. It creates a new category if the input is dissimilar from existing categories or updates an existing category if it's a good match.

- The network continues to learn and adapt to incoming data as you keep providing new input points over time.

- ART networks are sensitive to the `vigilance` parameter. Experiment with different values to control the network's behavior and adapt it to your specific application.

- This is a basic and simplified ART implementation for educational purposes. Real-world applications may require additional optimizations and considerations.

Please note that this implementation is a simplified version of ART and may not include all the intricacies and optimizations found in a full-scale ART implementation.
_____________________________________________________________________________________________________________________________________________________________________
