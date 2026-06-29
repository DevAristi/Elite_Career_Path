import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neural_network import MLPClassifier
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay, classification_report

print("--- INITIALIZING FRAUD DETECTION PIPELINE ---")

# DATA LOADING AND CLEANING
print("[-] Loading real PaySim dataset...")
# 'nrows=300000' limits rows to optimize local RAM usage and accelerate training cycles
df = pd.read_csv('paysim.csv', nrows=300000) 

print(f"[-] Records loaded: {df.shape[0]}. Starting preprocessing...")

# Column mapping dictionary to standardize features into clean formatting
column_mapping = {
    'step': 'Time_Step',
    'type': 'Transaction_Type',
    'amount': 'Amount',
    'oldbalanceOrg': 'Old_Balance_Orig',
    'newbalanceOrig': 'New_Balance_Orig',
    'oldbalanceDest': 'Old_Balance_Dest',
    'newbalanceDest': 'New_Balance_Dest',
    'isFraud': 'Is_Fraud'
}

df_renamed = df.rename(columns=column_mapping)

# Remove unique text identifiers that cause overfitting or data leakage
columns_to_drop = ['nameOrig', 'nameDest', 'isFlaggedFraud']
df_cleaned = df_renamed.drop(columns=[col for col in columns_to_drop if col in df_renamed.columns], errors='ignore')

# One-Hot Encoding for categorical features (Transaction Type)
df_cleaned = pd.get_dummies(df_cleaned, columns=['Transaction_Type'], drop_first=True)

# Strict dropping of missing rows to maintain data integrity
df_cleaned = df_cleaned.dropna()

# Isolation of independent variables (X) and target supervised binary label (y)
X = df_cleaned.drop('Is_Fraud', axis=1)
y = df_cleaned['Is_Fraud']
print(f"[-] Input tensor dimensions (X): {X.shape}")

# Feature Scaling: Standardize datasets to stabilize and accelerate gradient descent convergence
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)


# EXPLORATORY DATA ANALYSIS (EDA) VISUALIZATION
print("\n[-] Generating Plot 1: Correlation Matrix Heatmap...")
plt.figure(figsize=(12, 8))
# Pearson correlation matrix calculation for linear relationship evaluation
sns.heatmap(df_cleaned.corr(), annot=False, cmap='coolwarm', linewidths=0.5)
plt.title("Feature Correlation Matrix (EDA)")
plt.tight_layout()
plt.show() 


# MODEL SELECTION AND DATA PARTITIONING
# 50/50 split setup. 'stratify=y' enforces identical fraud ratios across splits to counter severe class imbalance
X_train, X_test, y_train, y_test = train_test_split(
    X_scaled, y, test_size=0.50, random_state=42, stratify=y
)

# Multi-Layer Perceptron (MLP Neural Network) Deep Architecture Configuration
# Implements two deep hidden layers to model non-linear complex fraud patterns
mlp_model = MLPClassifier(
    hidden_layer_sizes=(32, 16), 
    activation='relu', 
    solver='adam', 
    max_iter=50, # Epoch limit to bound compute overhead on local instances
    random_state=42,
    verbose=True # Streams optimization history and loss values directly to stderr
)

print("\n[-] Executing Neural Network Forward/Backward Pass Optimization...")
mlp_model.fit(X_train, y_train)


# PREDICTION AND INFERENCE PHASE
print("\n[-] Running batch inference on isolated validation test tensor...")
y_pred = mlp_model.predict(X_test)


# CONFUSION MATRIX AND EVALUATION PERFORMANCE REPORT
print("\n--- CLASSIFICATION PERFORMANCE REPORT ---")
# Statistical breakdown covering Precision, Recall (Sensitivity), and F1-Score metrics
print(classification_report(y_test, y_pred, target_names=['Legitimate (0)', 'Fraud (1)']))

# Confusion Matrix Visual Generation
conf_matrix = confusion_matrix(y_test, y_pred)
visual_display = ConfusionMatrixDisplay(confusion_matrix=conf_matrix, display_labels=['Legitimate (0)', 'Fraud (1)'])

visual_display.plot(cmap='Reds')
plt.title("Confusion Matrix Evaluation - MLP Neural Network")
plt.tight_layout()
plt.show()