package us.hiku.sdk.sample;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AlertDialog;
import android.view.View;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.MenuItem;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import us.hiku.android.sdk.ApplicationAuthorizationHandler;
import us.hiku.android.sdk.DeviceSetupHandler;
import us.hiku.android.sdk.HikuSetupSDK;
import us.hiku.android.sdk.TutorialCompletedHandler;
import us.hiku.android.sdk.UserAuthenticationHandler;
import us.hiku.android.sdk.UserCancelledSetupHandler;

public class MainActivity extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener {

    private String DEFAULT_MSG = "<tap here to enter an email address>";

    private String mEmail;
    public static final String APP_ID =       "<your app id>";
    public static final String APP_SECRET =   "<your app secret>";

    HikuSetupSDK sdk;
    TextView emailTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.setDrawerListener(toggle);
        toggle.syncState();

        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);

        View header = navigationView.getHeaderView(0);

        sdk = HikuSetupSDK.getInstance(this);
        sdk.setAppId(APP_ID);
        sdk.setAppSecret(APP_SECRET);

        emailTextView = (TextView) header.findViewById(R.id.emailTextView);
        emailTextView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
                final EditText editText = new EditText(MainActivity.this);
                builder.setView(editText);
                builder.setTitle("Enter an email address.");
                builder.setPositiveButton("Login to Sample App", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        // Force an SDK logout of previous account
                        sdk.logoutUser(MainActivity.this);

                        String newEmail = editText.getText().toString();
                        // Update nav header
                        emailTextView.setText(newEmail);
                        mEmail = newEmail;
                        sdk.setEmail(newEmail);
                    }
                });
                AlertDialog dialog = builder.create();
                dialog.show();
            }
        });
    }

    @Override
    protected void onResume() {
        if (sdk.getEmail()!=null) {
            mEmail = sdk.getEmail();
            emailTextView.setText(mEmail);
        } else
            emailTextView.setText(DEFAULT_MSG);
        super.onResume();
    }

    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
    }

    @Override
    public boolean onNavigationItemSelected(MenuItem item) {
        // Handle navigation view item clicks here.
        int id = item.getItemId();

        if (id == R.id.nav_hiku) {
            // Start SDK setup
            sdk.setEmail(mEmail);
            sdk.startSetup(this, authorizationHandler, setupHandler,
                    authenticationHandler, cancelHandler, tutorialCompletedHandler);
        } else if (id == R.id.nav_manage) {
            if (sdk.getUserAuthenticationStatus()) {
                // Show user token
                Intent i = new Intent(this, UserActivity.class);
                startActivity(i);
            } else
                Toast.makeText(this,"User must be logged in", Toast.LENGTH_SHORT).show();
        }  else if (id==R.id.nav_help) {
            if (sdk.getUserAuthenticationStatus())
                // Show the hiku orientation videos
                sdk.launchOrientation(this);
            else
                Toast.makeText(this,"User must be logged in", Toast.LENGTH_SHORT).show();
        } else if (id == R.id.nav_logout) {
            HikuSetupSDK sdk = HikuSetupSDK.getInstance(this);
            sdk.logoutUser(this);
            emailTextView.setText(DEFAULT_MSG);
        }

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);
        return true;
    }

    // Sample callbacks
    private TutorialCompletedHandler tutorialCompletedHandler = new TutorialCompletedHandler() {
        @Override
        public void onCompletion() {
            String msg = String.format("User completed tutorial!");
            Toast.makeText(MainActivity.this, msg, Toast.LENGTH_SHORT).show();
        }
    };

    private UserCancelledSetupHandler cancelHandler = new UserCancelledSetupHandler() {
        @Override
        public void onCancel() {
            String msg = String.format("User cancelled setup!");
            Toast.makeText(MainActivity.this, msg, Toast.LENGTH_SHORT).show();
        }
    };

    private ApplicationAuthorizationHandler authorizationHandler = new ApplicationAuthorizationHandler() {
        @Override
        public void onAuthorization(boolean authorized) {
            String msg = String.format("Application authorization status: %b",
                    authorized);
            Toast.makeText(MainActivity.this, msg, Toast.LENGTH_SHORT).show();
        }
    };

    private UserAuthenticationHandler authenticationHandler = new UserAuthenticationHandler() {
        @Override
        public void onAuthentication(boolean authenticated) {
            String msg = String.format("User authentication status: %b",
                    authenticated);
            Toast.makeText(MainActivity.this, msg, Toast.LENGTH_SHORT).show();
        }
    };

    private DeviceSetupHandler setupHandler = new DeviceSetupHandler() {
        @Override
        public void onResult(boolean success) {
            String msg = String.format("Device Setup Status: %b", success);
            Toast.makeText(MainActivity.this, msg, Toast.LENGTH_SHORT).show();
        }
    };

}
