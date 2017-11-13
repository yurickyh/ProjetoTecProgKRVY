public class Map{
	/*public static String generate(){
		String[] ter = {"road", "mountain", "river"};
		String terreno = ter[(int)(Math.random()*3)];
		double sorteio = Math.random();
		int cristal = 0;
		if(sorteio < 0.7) cristal = 0;
		else if (sorteio < 0.95) cristal = 1;
		else cristal = 2;
		int ocupado = 0;
		String celula = "{" + terreno + ", " + cristal + ", " + ocupado + ", 0}";
		return celula;
	}

	public static void main(String[] args){	
		int row = 5;
		int col = 5;

		System.out.print("{");
		System.out.println("");
		System.out.print("{");
		System.out.print("{road, 0, 1, 0}");
		for (int i = 0; i < (col-1); i++){
			System.out.print(", ");
			System.out.print(generate());
		}	
		System.out.print("},");	
		for (int i = 0; i < (row-2); i++){
			System.out.println("");
			System.out.print("{");
			for (int j = 0; j < col; j++){
				if(j != (col-1)){
					System.out.print(generate());
					System.out.print(", ");
				}
				else{
					System.out.print(generate());
				}
			}
			System.out.print("},");
		}
		System.out.println("");
		System.out.print("{");		
		for (int i = 0; i < (col-1); i++){			
			System.out.print(generate());
			System.out.print(", ");
		}	
		System.out.print("{road, 0, 1, 0}}");
		System.out.println("");
		System.out.print("}");
	}*/

	public static String generate(){
		String[] ter = {"road", "mountain", "river"};
		String terreno = ter[(int)(Math.random()*3)];
		double sorteio = Math.random();
		int cristal = 0;
		if(sorteio < 0.7) cristal = 0;
		else if (sorteio < 0.95) cristal = 1;
		else cristal = 2;
		int ocupado = 0;
		String celula = terreno + " " + cristal + " " + ocupado + " 0 ";
		return celula;
	}

	public static void main(String[] args){	
		int row = 4;
		int col = 8;

		for (int i = 0; i < row; i++){
			for (int j = 0; j < col; j++){
				System.out.print(generate());
			}
		}
	}
}
