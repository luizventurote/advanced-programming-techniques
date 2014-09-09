var Tree = (function() {

	var Node = function(value){
		this.data = value;
		this.left = null;
		this.right = null;
	};

	Node.prototype.addChild = function(data) {
		if(data.id < this.data.id) {
			this.left = new Node(data);
		} else if (data.id > this.data.id) { 
			this.right = new Node(data);
		}
	};

	function Tree(root) {//Of course, root = root tree value.
		this.root = new Node(root);
		this.currentNode = this.root;
	};

	Tree.prototype.add = function(data, start) {
	
		this.currentNode = start || this.root;

		if(this.currentNode.data.id === data.id) {
			throw new Error("Tree already contains id.");
		}

		if(data.id < this.currentNode.data.id) {

			if(this.currentNode.left === null) { 
				this.currentNode.left = new Node(data); 
			} else {
	    		this.add(data, this.currentNode.left);
	  		}

		} else if(data.id > this.currentNode.data.id) {

	 		if(this.currentNode.right === null) {
	 			this.currentNode.right = new Node(data);
	 		} else {
	    		this.add(data, this.currentNode.right);
	  		}

		} else{
	  		throw new Error("Could not add data to the tree.");
		}

	};

	Tree.prototype.find = function(data) {

		var found = false;
		var node = this.root;
		var id = typeof data === "number" ? data : data.id;

		while(1) {
			
			if(node.data.id === id) {
				return node.data;
			}

			if(id < node.data.id) {
				node = node.left;
			} else if(id > node.data.id) { 
				node = node.right;
			}
		}
	};

  return Tree

}());