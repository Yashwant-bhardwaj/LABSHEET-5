import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QPushButton, QWidget, QLineEdit, QLabel
from PyQt5.QtCore import Qt
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
import networkx as nx

class GraphVisualizer(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Tree and Graph Visualizer")
        self.setGeometry(100, 100, 800, 600)

        # Initialize the main graph object
        self.graph = nx.Graph()

        # Set up the UI
        self.initUI()

    def initUI(self):
        # Central widget
        self.centralWidget = QWidget()
        self.setCentralWidget(self.centralWidget)

        # Layouts
        self.layout = QVBoxLayout()
        self.centralWidget.setLayout(self.layout)

        # Canvas for visualization
        self.figure, self.ax = plt.subplots()
        self.canvas = FigureCanvas(self.figure)
        self.layout.addWidget(self.canvas)

        # Input for nodes and edges
        self.node_input = QLineEdit(self)
        self.node_input.setPlaceholderText("Enter node (e.g., A)")
        self.layout.addWidget(self.node_input)

        self.edge_input = QLineEdit(self)
        self.edge_input.setPlaceholderText("Enter edge (e.g., A B)")
        self.layout.addWidget(self.edge_input)

        # Buttons
        self.add_node_btn = QPushButton("Add Node", self)
        self.add_node_btn.clicked.connect(self.add_node)
        self.layout.addWidget(self.add_node_btn)

        self.add_edge_btn = QPushButton("Add Edge", self)
        self.add_edge_btn.clicked.connect(self.add_edge)
        self.layout.addWidget(self.add_edge_btn)

        self.clear_btn = QPushButton("Clear Graph", self)
        self.clear_btn.clicked.connect(self.clear_graph)
        self.layout.addWidget(self.clear_btn)

        self.update_graph()

    def add_node(self):
        node = self.node_input.text()
        if node:
            self.graph.add_node(node)
            self.node_input.clear()
            self.update_graph()

    def add_edge(self):
        edge = self.edge_input.text()
        if edge:
            nodes = edge.split()
            if len(nodes) == 2:
                self.graph.add_edge(nodes[0], nodes[1])
                self.edge_input.clear()
                self.update_graph()

    def clear_graph(self):
        self.graph.clear()
        self.update_graph()

    def update_graph(self):
        self.ax.clear()
        nx.draw(self.graph, with_labels=True, ax=self.ax, node_color="skyblue", node_size=2000, font_size=10)
        self.canvas.draw()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = GraphVisualizer()
    window.show()
    sys.exit(app.exec_())
