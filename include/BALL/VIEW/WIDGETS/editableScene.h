/*    THIS IS EXPERIMENTAL CODE  
 *
 *    WE GIVE NO WARRANTY
 *    
 *    USE AT YOUR OWN RISK!!!!!!
 */

#ifndef BALL_VIEW_WIDGETS_EDITABLESCENE_H
#define BALL_VIEW_WIDGETS_EDITABLESCENE_H


#ifndef BALL_KERNEL_SYSTME_H
#include <BALL/KERNEL/system.h>
#endif

#ifndef BALL_VIEW_WIDGETS_SCENE_H
#include <BALL/VIEW/WIDGETS/scene.h>
#endif

#ifndef BALL_KERNEL_MOLECULE_H
#include <BALL/KERNEL/molecule.h>
#endif

#ifndef BALL_VIEW_KERNEL_COMMON_H
# include <BALL/VIEW/KERNEL/common.h>
#endif 

#ifndef BALL_MATHS_VECTOR2_H
# include <BALL/MATHS/vector2.h>
#endif

namespace BALL
{
	namespace VIEW
	{

class EditSettings;

class BALL_VIEW_EXPORT EditableScene
	: public Scene
{
	Q_OBJECT //macro for QT-Messages

	public:

	BALL_EMBEDDABLE(EditableScene, ModularWidget)	

	// This class represents a single edit operation and stores its type and
	// parameters. This can be used to implement undo functionality.
	class BALL_VIEW_EXPORT EditOperation
	{
		public:

		/// Constructor
		EditOperation()
			throw();

		///
		EditOperation(Atom* atom, Bond* bond, String description= "Added Object", int operation=0)
			throw();

		///
		EditOperation(const EditOperation& eOperation)
			throw();

		/// Destructor.
		virtual ~EditOperation()
			throw();

		///
		enum OperationType
		{
			DEFAULT,
			ADDED__ATOM,
			ADDED__BOND,
			CHANGED__TYPE
				// DELETED__ATOM
				// DELETED__BOND
				//CHANGED__SYSTEM
				//MOVED__ATOM
		};

		int	operationType;
		Atom* atom;
		Bond* bond;
		String description;
	};

	///
	enum EditMode
	{
		// 
		EDIT__MODE = PICKING__MODE + 1
	};

	///
	EditableScene()
		throw();

	/// Default Constructor
	EditableScene(QWidget* parent_widget, const char* name = NULL, Qt::WFlags w_flags = 0)
		throw();

	/// Copy constructor.
	EditableScene (const EditableScene& eScene, QWidget* parent_widget = NULL, const char* name = NULL, Qt::WFlags wflags = 0)
		throw();

	/// Destructor.
	virtual ~EditableScene()
		throw();

	///
	void initializeWidget(MainControl& main_control)
		throw();

	///
	void checkMenu(MainControl& main_control)
		throw();

	///
	void initializePreferencesTab(Preferences &preferences)
		throw();
	
	///
	void finalizePreferencesTab(Preferences &preferences)
		throw();

	///
	virtual void applyPreferences()
		throw();
	
	///
	void showContextMenu(QPoint pos);

	///
	virtual void setMode(ModeType mode)
		throw();

	////////////////////////////////////////
	public slots:

	virtual void mousePressEvent(QMouseEvent* e);
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent *e);
	virtual void wheelEvent(QWheelEvent* qmouse_event);
	void switchShowGrid();

	// slots for communication with PTEDialog
	void setEditElementType(int element_number);
	int getEditElementType();
							
	////////////////////////////////////////
	protected slots:

	virtual void editMode_();
	void deleteAtom_();
	void changeElement_();
	void deleteBond_();
	void changeBondOrder_();
	void activatedOrderItem_(QAction* action);
	void moveAtom_();
	void atomProperties_();
	void createMolecule_();

	////////////////////////////////////////
	signals:

	// signal for communication with EditOperationDialog
	void newEditOperation(EditableScene::EditOperation &eo);

	////////////////////////////////////////
	protected:

	virtual void onNotify(Message *message)
		throw();

	/**
	 * Insert a given Atom in the Scene. Its position is specified by the 2-dim 
	 * Mouseclick coordinates of the Screen, which will be translated into the 
	 * 3-dim space of Viewing Volume.
	 */
	void insert_(int x_, int y_, PDBAtom &atom_);

	/**
	 *  Given a 3-dim. Coordinates (in Viewing Volume) getScreenPosition
	 *  computes the 2-dim Coordinates on Screen.
	 */
	TVector2<Position> getScreenPosition_(Vector3 vec);

	/**
	 * Given 2-dim Coordinates of Screen, clickedPointOnViewPlane computes the
	 * appropriate 3-dim Position in Viewing Volume
	 */
	Vector3 get3DPosition_(int x, int y);

	/**
	 * Given 2-dim Coordinates of Screen, getCLickedAtom_ returns the nearest Atom 
	 * within a special radius. If no atom is found, getClickedAtom returns NULL.
	 */
	Atom* getClickedAtom_(int x, int y);

	/**
	 * Given 2-dim Coordinates of Screen, getCLickedBond returns the nearest Bond
	 * within a special radius. If no bond is found, getClickedBond returns NULL.
	 * Note: This code is very similar to that of getClickedAtom and the two might
	 *       be joined in the future.
	 */
	Bond* getClickedBond_(int x, int y);

	/**
	 * Maps the current viewplane to screen coordinates.
	 * Returns false if the projection matrix is not correctly
	 * initialized.
	 */
	bool mapViewplaneToScreen_();

	virtual void paintGL();

	void init_();

	String getBondOrderString_(Index order);

	List<AtomContainer*> getContainers_();

	void changeBondOrder_(Index delta);
	void deselect_();
	void renderGrid_();

	QAction* edit_id_;	
	Atom* current_atom_;
	Bond* current_bond_;

	Vector3 near_left_bot_;  //TODO:: name in XYZ left_bot_mnear
	Vector3 near_right_bot_;
	Vector3 near_left_top_;

	Vector3 atom_pos_;
	bool draw_line_;
	bool draw_grid_;

	// search range when looking for atoms/bonds (in angstrom)
	static float atom_limit_;			
	static float bond_limit_;			
	// pick atoms/bonds only in highlighted AtomContainer?
	static bool only_highlighted_;
	// element for new atoms
	int atom_type_;
	// order for new bonds
	int bond_order_;
	Position last_y_;
	Qt::MouseButtons last_buttons_;

	//undo stack
	vector<EditOperation> undo_;
	EditSettings* edit_settings_;
};

	}//end of namespace
} // end of namespace
#endif