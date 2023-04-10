# %%
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LogisticRegression as LR
from sklearn.metrics import confusion_matrix
from sklearn.metrics import roc_curve, roc_auc_score

# %%

#Q1. plot the function curve with 500 points
# Define the function
def f(x):
    return x**3 + 5*x**2 + 7*x + 2

# Define the range and number of points
x_min = -4
x_max = 2
n_points = 500

# Generate the x-values
x_values = np.linspace(x_min, x_max, n_points)

# Evaluate the function at each x-value
y_values = f(x_values)

# Print the first 10 points for verification
for i in range(10):
    print(f"({x_values[i]}, {y_values[i]})")

plt.scatter(x_values, y_values, s=5)
plt.xlabel('x')
plt.ylabel('f(x)')
plt.title('Function f(x) = x^3 + 5x^2 + 7x + 2')
plt.show()



# %%
#Q2. adding noise and splitting the data


# Select 30% of the indices at random
num_points = n_points
num_noise_points = int(0.3 * num_points)
noise_indices = np.random.choice(num_points, num_noise_points, replace=False)

# Add Gaussian noise to the selected points
noise_scale = 10.0
y_values[noise_indices] += np.random.normal(0, noise_scale, num_noise_points)

# Divide the points into train and test sets
train_ratio = 0.8
train_size = int(train_ratio * num_points)
train_indices = np.random.choice(n_points, train_size, replace=False)
test_indices = np.setdiff1d(np.arange(n_points), train_indices)

train_x = x_values[train_indices]
train_y = y_values[train_indices]
test_x = x_values[test_indices]
test_y = y_values[test_indices]

# Plot the points with noise
plt.scatter(train_x, train_y, s=5, color="blue", label="train")
plt.scatter(test_x, test_y, s=5, color="orange", label="test")
plt.xlabel('x')
plt.ylabel('f(x) with noise')
plt.title('Function f(x) = x^3 + 5x^2 + 7x + 2 with 30% noise')
plt.legend()
plt.show()


# %%
#Q3. Linear Regression Model

# Define the linear regression function using gradient descent
def linear_regression(x, y, learning_rate=0.01, n_iterations=100):
    # Initialize the parameters
    m = 0
    b = 0

    # Define the cost function
    n = len(x)
    cost_history = []
    for i in range(n_iterations):
        y_predicted = m * x + b
        cost = np.sum((y_predicted - y)**2) / n
        cost_history.append(cost)

        # Update the parameters using the gradient descent algorithm
        m_gradient = (1/n) * np.sum(x * (y_predicted - y))
        b_gradient = (1/n) * np.sum(y_predicted - y)
        m -= learning_rate * m_gradient
        b -= learning_rate * b_gradient

    return m, b, cost_history

# Train the linear regression model on the train set
m, b, cost_history = linear_regression(train_x, train_y)

# Print the model parameters
print('m =', m)
print('b =', b)

# Plot the cost history
plt.plot(cost_history)
plt.xlabel('Iteration')
plt.ylabel('Cost')
plt.title('Cost history for linear regression')
plt.show()

# Plot the data points and the linear regression line
plt.scatter(train_x, train_y, s=5)
plt.plot(train_x, m*train_x + b, color='red')
plt.xlabel('x')
plt.ylabel('f(x) with noise')
plt.title('Linear regression model on train set')
plt.show()


# %%
#Q4.Calculate train and test error

# Evaluate the model on the train set
train_y_predicted = m * train_x + b
train_mse = np.mean((train_y_predicted - train_y)**2)
print('Train MSE:', train_mse)

# Evaluate the model on the test set
test_y_predicted = m * test_x + b
test_mse = np.mean((test_y_predicted - test_y)**2)
print('Test MSE:', test_mse)

'''# Plot the data points and the linear regression line on the train set
plt.scatter(train_x, train_y, s=5)
plt.plot(train_x, train_y_predicted, color='red')
plt.xlabel('x')
plt.ylabel('f(x) with noise')
plt.title('Linear regression model on train set')
plt.show()'''

# Plot the data points and the linear regression line on the test set
plt.scatter(test_x, test_y, s=5)
plt.plot(test_x, test_y_predicted, color='red')
plt.xlabel('x')
plt.ylabel('f(x) with noise')
plt.title('Linear regression model on test set')
plt.show()


# %%
#Q5. Fitting quadratic and cubic models

# Fit a quadratic model to the train set
a,b,c=np.polyfit(train_x, train_y, 2)

print('Quadratic model coefficients:',"|a: ", a,"|b: ",b,"|c: ",c)


# Evaluate the quadratic model on the test set
test_x_squared = test_x**2
X_quadratic_test = np.column_stack((test_x, test_x_squared))
test_y_predicted_quadratic = a*test_x_squared + b*test_x + c
test_mse_quadratic = np.mean((test_y_predicted_quadratic - test_y)**2)


# Fit a cubic model to the train set
a,b,c,d=np.polyfit(train_x, train_y, 3)

print('Cubic model coefficients:'," |a: ", a," |b: ",b," |c: ",c," |d: ",d)


# Evaluate the cubic model on the test set
test_x_cubed = test_x**3
X_cubic_test = np.column_stack((test_x, test_x_squared, test_x_cubed))
test_y_predicted_cubic = a*test_x_cubed + b*test_x_squared + c*test_x + d
test_mse_cubic = np.mean((test_y_predicted_cubic - test_y)**2)

print('\n')

#printing the test errors of each model
print('Test MSE (linear model):', test_mse)
print('Test MSE (quadratic model):', test_mse_quadratic)
print('Test MSE (cubic model):', test_mse_cubic)
print('\n')
print("From the results, its evident that the cubic model offers more flexibility and more closely fits the curve")

# Plot the data points and the linear, quadratic, and cubic regression lines on the test set
plt.scatter(test_x, test_y, s=5)
plt.plot(test_x, test_y_predicted, color='red', label='Linear model')
plt.plot(test_x, test_y_predicted_quadratic, color='green', label='Quadratic model')
plt.plot(test_x, test_y_predicted_cubic, color='orange', label='Cubic model')
plt.xlabel('x')
plt.ylabel('f(x) with noise')
plt.title('Linear, quadratic, and cubic regression models on test set')
plt.legend()
plt.show()


# %%
#Q6. assigning class labels to points

class_1_indices = x_values < 0
class_2_indices = x_values >= 0

# Plot the points with different colors for the two classes
plt.scatter(x_values[class_1_indices], y_values[class_1_indices], s=5, color='blue', label='Class 1')
plt.scatter(x_values[class_2_indices], y_values[class_2_indices], s=5, color='red', label='Class 2')

# Add labels and title
plt.xlabel('x')
plt.ylabel('y')
plt.title('Plot of f(x) with two classes')

# Add legend
plt.legend()

# Show the plot
plt.show()


# %%
#Q7. Logistic regression and confusion matrix

#defining logistic regression
class LogisticRegression:
    def __init__(self, learning_rate=0.1, num_iterations=100):
        self.learning_rate = learning_rate
        self.num_iterations = num_iterations

    def sigmoid(self, z):
        return 1 / (1 + np.exp(-z))

    def fit(self, X, y):
        m, n = X.shape
        self.theta = np.zeros(n)
        for i in range(self.num_iterations):
            z = np.dot(X, self.theta)
            h = self.sigmoid(z)
            gradient = np.dot(X.T, (h - y)) / m
            self.theta -= self.learning_rate * gradient

    def predict_proba(self, X):
        z = np.dot(X, self.theta)
        h = self.sigmoid(z)
        return np.vstack((1 - h, h)).T

    def predict(self, X):
        z = np.dot(X, self.theta)
        h = self.sigmoid(z)
        y_pred = np.round(h)
        return y_pred

#assigning y_values to the red and blue set
y_values[class_1_indices] = 0
y_values[class_2_indices] = 1

# Create the train and test sets
train_ratio = 0.8
train_size = int(train_ratio * len(x_values))
permuted_indices = np.random.permutation(len(x_values))
train_indices = permuted_indices[:train_size]
test_indices = permuted_indices[train_size:]

x_train = x_values[train_indices].reshape(-1, 1)
y_train = y_values[train_indices]
x_test = x_values[test_indices].reshape(-1, 1)
y_test = y_values[test_indices]

# Create an instance of the logistic regression class
model = LogisticRegression()

# Fit the model to the training set
model.fit(x_train, y_train)

# Predict the classes of the test set
y_pred = model.predict(x_test)

# Plot the decision boundary
x_boundary = np.linspace(-4, 2, 1000).reshape(-1, 1)
y_boundary = model.predict(x_boundary)
plt.plot(x_boundary, y_boundary, color='green', linewidth=1, label='decision boundary')

# Plot the test points with different colors for the two classes
plt.scatter(x_test[y_test == 0], y_test[y_test == 0], s=10, color='blue', label='Class 1')
plt.scatter(x_test[y_test == 1], y_test[y_test == 1], s=10, color='red', label='Class 2')

# Add labels and title
plt.xlabel('x')
plt.ylabel('y')
plt.title('Logistic Regression Model with Decision Boundary')

# Add legend
plt.legend()

# Show the plot
plt.show()

# Compute and print the confusion matrix for the test set
cm = confusion_matrix(y_test, y_pred)
print('Confusion matrix for the test set:')
print(cm)

# %%
#Q8. calculate the roc curve and AUC score

# Compute the ROC curve and AUC
y_prob=model.predict_proba(x_test)[:, 1]
fpr, tpr, thresholds = roc_curve(y_test, y_prob)
auc = roc_auc_score(y_test, y_prob)

# Plot the ROC curve
plt.plot(fpr, tpr, color='blue', label='ROC curve')
plt.plot([0, 1], [0, 1], color='red', linestyle='-.', label='Random guess')
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('Receiver Operating Characteristic (ROC) Curve\nAUC = {:.3f}'.format(auc))
plt.legend()
plt.show()

# Print the AUC
print('AUC:', auc)

# %%



